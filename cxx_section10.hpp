#include <iostream>
#include "string.h"

class P_Node;

class Picture
{
    friend Picture reframe(const Picture&, char, char, char);
    friend std::ostream& operator<<(std::ostream&, const Picture&);
    friend Picture frame(const Picture&);
    friend Picture operator&(const Picture&, const Picture&);
    friend Picture operator|(const Picture&, const Picture&);

    friend class String_Pic;
    friend class Frame_Pic;
    friend class HCat_Pic;
    friend class VCat_Pic;

public:
    Picture(const char* const*, int);
    Picture(const Picture&);
    Picture& operator=(const Picture&);
    ~Picture();

private:
    P_Node* m_p;
    //这个构造函数作为隐式转型操作符，应用于链接操作
    Picture(P_Node*);
    int height() const;
    int width() const;
    void display(std::ostream&, int, int) const;
};

class P_Node
{
    friend class Picture;
    friend Picture reframe(const Picture&, char, char, char);
protected:
    P_Node();
    virtual ~P_Node();
    virtual int height() const = 0;
    virtual int width() const = 0;
    virtual void display(std::ostream&, int, int) const = 0;
    int max(int x, int y) const;
    virtual Picture reframe(char, char, char) = 0;
    int m_use;
};

class String_Pic: public P_Node
{
    friend class Picture;
    String_Pic(const char* const*, int);
    ~String_Pic();
    int height() const;
    int width() const;
    void display(std::ostream&, int, int) const;
    Picture reframe(char c, char s, char t);

    char** m_data;
    int m_size;
};

class Frame_Pic: public P_Node
{
    friend Picture frame(const Picture&);
    Frame_Pic(const Picture&, char c='+', char s='|', char t='-');
    int height() const;
    int width() const;
    void display(std::ostream&, int, int) const;
    Picture reframe(char c, char s, char t);

    Picture m_p;
    char m_corner;
    char m_sideBorder;
    char m_topBorder;
};

class VCat_Pic: public P_Node
{
    friend Picture operator&(const Picture&, const Picture&);
    VCat_Pic(const Picture&, const Picture&);
    int height() const;
    int width() const;
    void display(std::ostream&, int, int) const;
    Picture reframe(char c, char s, char t);

    Picture m_top;
    Picture m_bottom;
};

class HCat_Pic: public P_Node
{
    friend Picture operator|(const Picture&, const Picture&);
    HCat_Pic(const Picture&, const Picture&);
    int height() const;
    int width() const;
    void display(std::ostream&, int, int) const;
    Picture reframe(char c, char s, char t);

    Picture m_left;
    Picture m_right;
};

//todo: cpp
Picture reframe(const Picture& pic, char c, char s, char t)
{
    return pic.m_p->reframe(c, s, t);
}

std::ostream& operator<<(std::ostream& os, const Picture& picture)
{
    int ht = picture.height();
    for (int i=0; i<ht; ++i)
    {
        picture.display(os, i, picture.width());
        os << std::endl;
    }
    return os;
}


int P_Node::max(int x, int y) const
{
    return x > y ? x : y;
}

P_Node::P_Node()
    :m_use(1)
{
}

P_Node::~P_Node()
{
}
/************end Picture****************/


String_Pic::String_Pic(const char* const* array, int n)
    :m_data(new char* [n]), m_size(n)
{
    for (int i=0; i<n; ++i)
    {
        m_data[i] = new char[strlen(array[i]) + 1];
        strcpy(m_data[i], array[i]);
    }
}

String_Pic::~String_Pic()
{
    for (int i=0; i<m_size; ++i)
        delete[] m_data[i];
    delete[] m_data;
}

int String_Pic::height() const
{
    return m_size;
}

int String_Pic::width() const
{
    int n = 0;
    for (int i=0; i<m_size; ++i)
    {
        n = max(n, strlen(m_data[i]));
    }
    return n;
}

static void pad(std::ostream& os, int x, int y)
{
    for (int i=x; i<y; ++i)
    {
        os << " ";
    }
}

void String_Pic::display(std::ostream& os, int row, int width) const
{
    int start = 0;
    if (row >= 0 && row < height())
    {
        os << m_data[row];
        start = strlen(m_data[row]);
    }
    pad(os, start, width);
}

Picture String_Pic::reframe(char, char, char)
{
    //增加引用计数,以表明还有另一个用户在使用底层的String_Pic,
    //使用P_Node*的转型操作从this生成一个新的Picture.
    ++m_use;
    return this;//使用私有Picture构造函数
}

/************end String_Pic****************/

Picture frame(const Picture& pic)
{
    return new Frame_Pic(pic);
}

Frame_Pic::Frame_Pic(const Picture& pic, char c, char s, char t)
    :m_p(pic), m_corner(c), m_sideBorder(s), m_topBorder(t)
{
}

int Frame_Pic::height() const
{
    return m_p.height() + 2;
}
int Frame_Pic::width() const
{
    return m_p.width() + 2;
}
void Frame_Pic::display(std::ostream& os, int row, int width) const
{
    if (row<0 || row>=height())
        pad(os, 0, width);
    else
    {
        if (row==0 || row==height()-1)
        {
            //顶框和底框
            os << m_corner;//"+";
            int i = m_p.width();
            while (--i >= 0)
                os<< m_topBorder;//"-";
            os << m_corner;//"+";
        }
        else
        {
            //内部行
            os << m_sideBorder;//"|";
            m_p.display(os, row-1, m_p.width());
            os << m_sideBorder;//"|";
        }
        pad(os, this->width(), width);
    }
}

Picture Frame_Pic::reframe(char c, char s, char t)
{
    return new Frame_Pic(::reframe(m_p, c, s, t), c, s, t);
}

/************end Frame_Pic****************/

VCat_Pic::VCat_Pic(const Picture& top, const Picture& bottom)
    :m_top(top), m_bottom(bottom)
{
}

Picture operator&(const Picture& top, const Picture& bottom)
{
    return new VCat_Pic(top, bottom);
}

int VCat_Pic::height() const
{
    return m_top.height() + m_bottom.height();
}
int VCat_Pic::width() const
{
    return max(m_top.width(), m_bottom.width());
}
void VCat_Pic::display(std::ostream& os, int row , int width) const
{
    if (row>=0 && row< m_top.height())
    {
        m_top.display(os, row, width);
    }
    else if (row < m_top.height() + m_bottom.height())
    {
        m_bottom.display(os, row-m_top.height(), width);
    }
    else
    {
        pad(os, 0, width);
    }
}

Picture VCat_Pic::reframe(char c, char s, char t)
{
    return new VCat_Pic(::reframe(m_top, c, s, t), ::reframe(m_bottom, c, s, t));
}

/************end VCat_Pic****************/


HCat_Pic::HCat_Pic(const Picture& left, const Picture& right)
    :m_left(left), m_right(right)
{
}

Picture operator|(const Picture& left, const Picture& right)
{
    return new HCat_Pic(left, right);
}

int HCat_Pic::height() const
{
    return max(m_left.height(), m_right.height());
}
int HCat_Pic::width() const
{
    return m_left.width() + m_right.width();
}
void HCat_Pic::display(std::ostream& os, int row, int width) const
{
    m_left.display(os, row, m_left.width());
    m_right.display(os, row, m_right.width());
    pad(os, this->width(), width);
}

Picture HCat_Pic::reframe(char c, char s, char t)
{
    return new HCat_Pic(::reframe(m_left, c, s, t), ::reframe(m_right, c, s, t));
}

/************end HCat_Pic****************/

Picture::Picture(P_Node* p)
    :m_p(p)
{
}

Picture::Picture(const char* const* array, int n)
    :m_p(new String_Pic(array, n))
{
}

Picture::Picture(const Picture& orig)
    :m_p(orig.m_p)
{
    orig.m_p->m_use++;
}

Picture& Picture::operator=(const Picture& orig)
{
    ++orig.m_p->m_use;
    if (--m_p->m_use == 0)
        delete m_p;
    m_p = orig.m_p;
    return *this;
}


Picture::~Picture()
{
    if (--m_p->m_use == 0)
        delete m_p;
}

int Picture::height() const
{
    return m_p->height();
}
int Picture::width() const
{
    return m_p->width();
}
void Picture::display(std::ostream& o, const int x, const int y) const
{
    m_p->display(o, x, y);
}

int section10()
{
    using namespace std;
    const char* init[] = {"Pairs", "in the", "Spring"};

    Picture p(init, 3);
    cout << p << endl;

    Picture q = p;
    cout << q << endl;

    Picture fq = frame(q);
    cout << fq << endl;

    Picture fqq = (fq & q);
    cout << fqq << endl;

    Picture  p_fqq = p | fqq;
    cout << p_fqq << endl;

    Picture fpfqq = frame(p_fqq);
    cout << fpfqq << endl;

    Picture re = reframe(fpfqq, '*', '!', '~');
    cout << re << endl;

    return 0;
}
