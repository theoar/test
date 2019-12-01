#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <tuple>

using namespace std;

typedef struct {
    short Field1 : 1;
    short Field2: 1;
    short Field3 : 1;
    short Field4 : 1;
} BitField;


class Pojazd {

  public:
    Pojazd(void)
    {
      Kolor = "def";
      Marka = "def";
      Model = "def";
    }

    Pojazd(const string & Kolor_, const string & Marka_, const string & Model_)
    {
      Kolor = Kolor_;
      Marka = Marka_;
      Model = Model_;
      cout << __FUNCTION__ << endl;
    }
    Pojazd(const Pojazd & Other ) {
      Kolor=Other.Kolor;
      Marka=Other.Marka;
      Model=Other.Model;
    }

    const Pojazd & operator=(const Pojazd & Other)
    {
      Kolor=Other.Kolor;
      Marka=Other.Marka;
      Model=Other.Marka;

      return *this;
    }

    virtual ~Pojazd() { return; }

    virtual void jedz(void) { return; }
    virtual void stop(void) { return; }
    virtual void skrec(short x) { return; }

    string getKolor() const { return Kolor; }
    void setKolor(const string &value) { Kolor=value; }

    string getMarka() const { return Marka; }
    void setMarka(const string &value) { Marka=value; }

    string getModel() const { return Model; }
    void setModel(const string &value) { Model=value; }

  protected:
    string Kolor;
    string Marka;
    string Model;

};


class Samochod : public Pojazd {
  public:
    using Pojazd::Pojazd;

    virtual ~Samochod() { return; }

    const Samochod & operator=(const Samochod & Other)
    {
      Marka=Other.Marka;
      Kolor=Other.Kolor;
      Model=Other.Model;

      return *this;
    }


    void jedz(void) { return; }
    void stop(void) { return; }
    void skrec(short x) { return; }

    void print(void) {
      cout << Model << endl;
      cout << Marka << endl;
      cout << Kolor << endl;
    }
};

void Foo(void)
{
  cout<<__FUNCTION__<<endl;
  cout<<"Hello"<<endl;
}


void FooTest(shared_ptr<Samochod> & Ptr)
{
  auto X = Ptr;
  cout << X.use_count() << endl;
  X->print();
}


template<int R, int C, typename T> decltype (auto) summ(T Matrix[R][C])
{
  T Sum = 0;
  for(int Rows = 0; Rows<R; ++Rows)
    for(int Cols = 0; Cols<C; ++Cols)
      Sum+=(Matrix[Rows][Cols]=static_cast<T>(1.12));

  return Sum;
}

class Test
{
  private:
    int X = 0;
  public:
    Test(int X_) { cout<<"Konstruktor " << endl; X=X_; }
    Test(const Test & T) { cout<<"Konstruktor kopiujacy" << endl; X=T.X;}
    Test(const Test && T) { cout<<"Konstruktor przenoszacy" << endl; X=T.X; }

    Test & operator=(const Test & T) { cout<< "Operator przypisania" << endl; X=T.X; return *this; }
    Test & operator=(const Test && T) { cout << "Operator przypisania - przeniesienie" << endl; X=T.X; return *this;}

    void setX(int X_) { X=X_; }
    void print(void){ cout << X << endl;}

};


Test  initKeppo()
{
  return Test(123);
}


int main()
{

  std::tuple<int, double, string> tuple(10, 12.3, "keppo");
  cout << get<0>(tuple) << endl;
  cout << get<1>(tuple) << endl;
  cout << get<2>(tuple) << endl;
  Samochod S1{"Czarny", "Fiat", "Tipo"};
  Samochod S2{"Bialy", "Fiat", "Seicento"};
  Samochod &P1 = S1;
  P1=S2;

  P1.print();

  //function pointer via full declaration
  void (*FncPtr)(void) = &Foo;
  FncPtr();

  //function pointer via auto
  auto FncPtr2 = &Foo;
  FncPtr2();

  //method ptr via full declaration
  typedef void (Samochod::*FncPtrType)(void);
  FncPtrType FncPtr1= &Samochod::print;
  (S1.*FncPtr1)();

  //method ptr via auto
  auto MPtr = &Samochod::print;
  (S1.*MPtr)();

  auto SharedToCar1_0 = shared_ptr<Samochod>(new Samochod("Bialy", "Fiat", "Seicento"));
  auto MakedShared = make_shared<Samochod>("taki", "jako", "taki");
  auto SecondShared = MakedShared;

  auto Unique = make_unique<Samochod>("bla", "bla", "bla");
  auto MovedUnique = unique_ptr<Samochod>(Unique.release());
  cout << " ptr:" <<Unique.get() << endl;
  cout << " ptr:" <<MovedUnique.get() << endl;

  int **Table = new int*[5];
  cout << endl;
  for(int x = 0; x<5; ++x)
    {
      Table[x] = new int[6];
      for(int y = 0; y<6; ++y)
	{
	  cout << (Table[x][y] = y*x);
	  cout << " ";
	}

      cout << endl;

    }
  cout << endl;

  for(int x = 0; x<5; ++x)
    delete [] Table[x];
  delete [] Table;


  Samochod **ObjTable = new Samochod*[10];

  for(int z = 0; z<10; ++z)
    {
      ObjTable[z] = new Samochod;
      delete ObjTable[z];
    }

  delete [] ObjTable;

  int X = 69;
  auto Lambda = [&X](void)  { X++; };
  Lambda();
  cout << "X: " << X << endl;


  const int Rows = 10;
  const int Cols = 10;
  float Matrix[Rows][Cols];

  cout << summ<Rows, Cols, float>(Matrix) << endl;


  return 0;
}


