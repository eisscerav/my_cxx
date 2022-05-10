#include <iostream>
#include <cstring>
#include <string.h>

class Picture
{
public:
Picture();
    Picture(const char**, int);
    Picture(const Picture&);
    Picture& operator=(const Picture&);
    ~Picture();

private:
    int m_height;
    int m_width;
    char* m_data;

    char& position(int row, int col)
    {
        return m_data[row * m_width + col];
    }

    char position(int row, int col) const
    {
        return m_data[row * m_width + col];
    }

    void init(int height, int width);
    static int max(int m, int n);
    void copyBlock(int m, int n, const Picture&);
    void clear(int x, int y, int height, int width);

    friend std::ostream& operator<<(std::ostream&, const Picture&);
    friend Picture frame(const Picture&);
    friend Picture operator&(const Picture&, const Picture&);
    friend Picture operator|(const Picture&, const Picture&);
};

Picture::Picture()
    :m_height(0), m_width(0), m_data(0)
{
}

Picture::Picture(const char* array[], int n)
{
    int w = 0;
    for (int i = 0; i < n; i++)
    {
        w = Picture::max(w, int(strlen(array[i])));
    }

    init(n, w);

    for (int i = 0; i<n; i++)
    {
        const char* src = array[i];
        int len = strlen(src);
        int j = 0;

        while (j < len)
        {
            position(i, j) = src[j];
            ++j;
        }
        //给每一行中余下的位置要添上空格
        while (j< m_width)
        {
            position(i, j) = ' ';
            ++j;
        }
    }
}

Picture::Picture(const Picture& p)
     :m_height(p.m_height), m_width(p.m_width),
      m_data(new char[p.m_height * p.m_width])
{
    copyBlock(0 ,0 ,p);
}

Picture& Picture::operator=(const Picture& p)
{
    if (this != &p)
    {
        delete[] m_data;
        init(p.m_height, p.m_width);
        copyBlock(0, 0, p);
    }
    return *this;
}

Picture::~Picture()
{
}

void Picture::init(int height, int width)
{
    m_height = height;
    m_width = width;
    m_data = new char[height * width];

}

int Picture::max(int m, int n)
{
    return m>n ? m:n;
}

void Picture::copyBlock(int m, int n, const Picture& p)
{
    for (int i = 0; i < p.m_height; i++)
    {
        for (int j = 0; j < p.m_width; j++)
        {
            position(i + m, j + n) = p.position(i, j);
        }
    }
}

void Picture::clear(int x, int y, int height, int width)
{
    for (int i = x; i < height; ++i)
    {
        for (int j = y; j < width; ++j)
        {
            position(i, j) = ' ';
        }
    }
}

std::ostream& operator<<(std::ostream& o, const Picture& p)
{
    for (int i = 0; i < p.m_height; i++)
    {
        for (int j = 0; j < p.m_width; j++)
        {
            o << p.position(i, j);
        }
        o << std::endl;
    }
    return o;
}

Picture frame(const Picture& p)
{
    Picture r;
    r.init(p.m_height + 2, p.m_width + 2);

    //左右两边边框“|”
    for (int i = 1; i< r.m_height - 1; ++i)
    {
        r.position(i, 0) = '|';
        r.position(i, r.m_width - 1) = '|';
    }
    //上下边框“-”
    for (int j = 1; j < r.m_width - 1; ++j)
    {
        r.position(0, j) = '-';
        r.position(r.m_height - 1, j) = '-';
    }
    //四个角“+”
    r.position(0, 0) = '+';
    r.position(0, r.m_width - 1) = '+';
    r.position(r.m_height -1, 0) = '+';
    r.position(r.m_height -1, r.m_width - 1) = '+';

    r.copyBlock(1, 1, p);
    return r;
}

Picture operator&(const Picture& up, const Picture& down)
{
    Picture r;
    r.init(up.m_height + down.m_height,
           Picture::max(up.m_width, down.m_width));
    //将组合后的无用单元设置成空格
    r.clear(0, up.m_width, up.m_height, r.m_width);
    r.clear(up.m_height, down.m_width, r.m_height, r.m_width);

    r.copyBlock(0, 0, up);
    r.copyBlock(up.m_height, 0, down);
    return r;

}

Picture operator|(const Picture& left, const Picture& right)
{
    Picture r;
    r.init(Picture::max(left.m_height, right.m_height),
           left.m_width + right.m_width);
    r.clear(left.m_height, 0, r.m_height, left.m_width);
    r.clear(right.m_height, left.m_width, r.m_height, r.m_width);
    r.copyBlock(0, 0, left);
    r.copyBlock(0, left.m_width, right);

    return r;
}

int section9()
{
    const char* init[] = {"Pairs", "in the", "Spring"};

    Picture p(init, 3);
    std::cout << p << std::endl;

    Picture q = p;
    std::cout << q << std::endl;

    Picture fq = frame(q);
    std::cout << fq << std::endl;

    Picture fqq = (fq & q);
    std::cout << fqq << std::endl;

    Picture  p_fqq = p | (frame(q) & q);
    std::cout << p_fqq << std::endl;

    Picture fpfqq = frame(p_fqq);
    std::cout << fpfqq << std::endl;

    return 0;
}

