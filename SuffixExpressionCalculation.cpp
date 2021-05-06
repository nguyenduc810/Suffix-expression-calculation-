#include<iostream>
#include <string>
#include<conio.h>
#include<cctype>
#include<math.h>
using namespace std;
/*
Bài toán tính biểu thức toán học nhập vào 
*/

/*
Tạo 1 class node với khai báo dữ liệu trừu tương template
*/
template <class T>
class Node
{
    public:
      T value;
      Node * next;
      // Constructor
      Node()
      {
          value = NULL;
          next = NULL;
      }
      Node(T value)
      {
          this->value = value;
          next = NULL;
      }
};
/*
Xây dựng Stack với các thao tác:
push()   // thêm vào
pop()    // lấy ra
top()    // lấy phần tử đầu tiên
isEmpty   // Kiểm tra xem Stack có trống không
diplay()  // In ra thông tin
*/
template<class T>
class Stack
{
    public:
      Node<T> * head;
      int size;
      Stack()
      {
          head = NULL;
          size = 0;
      }
      void push(T value)
      {
          Node<T> * newNode = new Node<T>(value);
          if(isEmpty())
          {
              head = newNode;
              size++;
          }
          else
          {
              newNode->next = head;
              head = newNode;
              size++;
          }
      }
      T pop()
      {
          if(isEmpty())
          {
              cout<<"The stack is empty!";
              return NULL;
          }
          Node<T> * p = new Node<T>();
          p = head;
          head = head->next;
          T val = p->value;
          size--;
          delete p;
          return val;
      }
      int isEmpty()
      {
          return size == 0;
      }
     void disPlay()
      {
          Node<T> * p = new Node<T>();
          p = head;
          cout<<p->value<<"  ";
          while(p->next != NULL)
          {
              p = p->next;
              cout<<p->value<<"   ";
          }
      } 
      T top()
      {
          return head->value;
      }
};

string toPostFix();
int priority(char c);
int calculate( string s);
int operator1(int left, int right , char c);
int main ()
{
    string s = toPostFix();
    cout<<s;
    cout<<"\n"<<calculate(s);
    getch();
}
// Hàm xét thứ tự ưu tiện toán tử
int priority(char c)
{
    if(c == '+' || c == '-') return 1;
    if(c == '*' || c == '/' || c == '%') return 2;
    if(c == '^') return 3;
    return 0;
}
// Hàm chuyển đổi biểu thức trung tố về hậu tố dùng stack
string toPostFix()
{
    Stack<char> s;
    s.push('(');
    string str,str1="";
    cout<<"Input: ";
    getline(cin, str);
    str.push_back(')');
    int n = str.length(), i = 0, j = 0;
    while (i < n)
    {
        if(str[i] != ' ')                     
        {
            if(isdigit(str[i]) || isalpha(str[i])) str1 += str[i];        // Nếu kí tự là số hoặc chữ thì lưu vào xâu str1
            else
            {
                if(str[i] == '(') s.push(str[i]);                         // Nếu gặp dấu '(' thì đẩy vào stack
                else
                {
                    str1 +=' ';
                    if(str[i] == ')')                                    // Nếu gặp dấu ')' thì lấy hết các toán tử ra khỏi Stack cho đến khi 
                    {                                                    // gặp '(' và cho vào xâu str1
                        while(s.top() != '(')
                        {
                            str1 += s.pop();
                        }
                        s.pop();
                    }
                    else
                    {
                        while(priority(s.top()) >= priority(str[i]))     // Nếu gặp kí tự là toán tử thì xét thứ tự ưu tiên để lấy ra
                        {                                                // nếu nhỏ hơn thì lấy các toán tử ra khỏi stack cho đến khi lớn hơn  
                            str1 += s.pop();
                        }
                        s.push(str[i]);
                    }
                } 
            }
        }
        i++;
    }
    return str1;
}

// Hàm tính toán
int operator1(int left, int right , char c)
{
    if(c == '+') return left +right;
    if(c == '-') return left -right;
    if(c == '/') return left /right;
    if(c == '*') return left *right;
    if(c == '%') return left %right;
    if(c == '^') return pow(left, right);
}

//Hàm tính toán với biểu thức hậu tố dùng stack
int calculate( string s)
{
    Stack<int> st;
    int n = s.length(), i = 0, c = 0;
    while(i < n)
    {
        if(s[i] != ' ' && isdigit(s[i]))     //Nếu kí tự đọc vào là số
        {
            c++;                             // biến đếm dùng để đếm các chữ số của 1 số
        }
        else
        {
            if(s[i] == ' ')                  // Khi đã gặp dấu ' ' thì chuyển các kí tự vừa đọc thành số và đưa vào stack
            {
                int sum = 0;
                for(int j = i - c ; j < i ; j++ )
                {
                    int n = s[j] - '0'; 
                    c--;
                    sum += n*pow(10,c);
                }
                st.push(sum);
            }
            else                             // Nếu gặp kí tự là toán tử thì lấy từ stack ra các số và tính toán
            {
                int r = st.pop();
                int l = st.pop();
                st.push(operator1(l , r , s[i]));
            }
        }
        i++;
    }
    return st.top();                         // Trả về kết quả phép tính
}