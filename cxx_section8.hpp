#include <iostream>
#include <string>

class Expr_node;
class Int_node;
class Unary_node;
class Binary_node;

class Expr
{
public:
    Expr(int n);
//    {
//        p = new Int_node(n);
//    };

    Expr(const std::string op, Expr t);
//    {
//        p = new Unary_node(op, t);
//    }

    Expr(const std::string op, Expr lhs, Expr rhs);
//    {
//        p = new Binary_node(op, lhs, rhs);
//    }

    Expr(const Expr& t);
//    {
//        p = t.p;
//        ++p->use;
//    }

    Expr& operator=(const Expr &t);
//    {
//        t.p->use++;
//        if(--p->use == 0)
//            delete p;
//        p = t.p;
//        return *this;
//    }

    ~Expr();
//    {
//        if(--p->use == 0)
//        delete p;
//    }

//    {
//       t.p->print(o);
//       return o;
//    }
    int eval() const;
private:
    friend std::ostream& operator<<(std::ostream &o, Expr t);

    Expr_node *p;
};

class Expr_node
{
    friend class Expr;
    int use;

protected:
    Expr_node():use(1){};
    virtual ~Expr_node(){};

public:
    virtual void print(std::ostream &) = 0;
    virtual int eval() const = 0;
};

class Int_node : public Expr_node
{
    friend class Expr;

    int n_;
    Int_node(int n):n_(n){};

    virtual void print(std::ostream& o)
    {
        o << n_ ;
    }

    virtual int eval() const;

};

class Unary_node : public Expr_node
{
    friend class Expr;
    std::string op_;
    Expr t_;
//    Unary_node(std::string op, Expr t): op_(op), t_(t) {}
    Unary_node(std::string op, Expr t);
    virtual void print(std::ostream& o);
//    {
//        o << "(" << op_ << t_ << ")";
//    }
    virtual int eval() const;
};

class Binary_node : public Expr_node
{
    friend class Expr;
    std::string op_;
    Expr lhs_;
    Expr rhs_;
//    Binary_node(std::string op, Expr lhs, Expr rhs):op_(op), lhs_(lhs), rhs_(rhs) {}
    Binary_node(std::string op, Expr lhs, Expr rhs);
    virtual void print(std::ostream& o);
//    {
//        o << "(" << lhs_ << op_ << rhs_ << ")";
//    }
    virtual int eval() const;
};

int Int_node::eval () const
{
    return n_;
}

Unary_node::Unary_node(std::string op, Expr t): op_(op), t_(t) {}
void Unary_node::print(std::ostream& o)
{
    o << "(" << op_ << t_ << ")";
}

int Unary_node::eval() const
{
    if(op_ == "-")
        return t_.eval();
}

Binary_node::Binary_node(std::string op, Expr lhs, Expr rhs):op_(op), lhs_(lhs), rhs_(rhs) {}
void Binary_node::print(std::ostream& o)
{
    o << "(" << lhs_ << op_ << rhs_ << ")";
}
int Binary_node::eval() const
{
    int op1 = lhs_.eval();
    int op2 = rhs_.eval();

    if("+" == op_) return op1 + op2;
    if("-" == op_) return op1 - op2;
    if("*" == op_) return op1 * op2;
    if("/" == op_ && op2 != 0) return op1 / op2;
}

std::ostream& operator<<(std::ostream &o, Expr t)
{
   t.p->print(o);
   return o;
}

Expr::Expr(int n)
{
    p = new Int_node(n);
};

Expr::Expr(const std::string op, Expr t)
{
    p = new Unary_node(op, t);
}

Expr::Expr(const std::string op, Expr lhs, Expr rhs)
{
    p = new Binary_node(op, lhs, rhs);
}

Expr::Expr(const Expr& t)
{
    p = t.p;
    ++p->use;
}

Expr::~Expr()
{
    if(--p->use == 0)
        delete p;
}

Expr& Expr::operator=(const Expr &t)
{
    t.p->use++;
    if(--p->use == 0)
        delete p;
    p = t.p;
    return *this;
}

int Expr::eval() const
{
    return p->eval();
}

int main()
{
    /*
    Expr t = Expr("*", Expr("-", 5), Expr("+", 3, 4));
    std::cout << t << std::endl;
    t = Expr("*", t, t);
    std::cout << t << std::endl;
     */
    Expr t = Expr("*", Expr("-", 5), Expr("+", 3, 4));
    std::cout << t << "=" << t.eval() << std::endl;
    t = Expr("*", t, t);
    std::cout << t << "=" << t.eval() << std::endl;
    return 0;
}
