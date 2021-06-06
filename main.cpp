#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;

char point=5,underLine=254,q=178,g=5,bd2=221;

int gotoxy (int x, int y)
{
   COORD loc;
   loc.X=x;
   loc.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),loc);
}

void decSubTopic(string decWord, int X = 48, int Y = 6)
{
    int j;
    gotoxy(X,Y);
    for(j=0;j<10;j++)
    {
      Sleep(50);
      if(j<5)
      {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
        cout<<bd2;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
      }
      else
        cout<<bd2;
    }
    cout<<" ";
    for(j=0;j<decWord.length();j++)
    {
      Sleep(50);
      cout<<decWord[j];
    }
    cout<<"  ";
    for(j=0;j<10;j++)
    {
      Sleep(50);
      if(j>5)
      {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
        cout<<bd2;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
      }
      else
        cout<<bd2;
    }
}

class Node
{
public:
    int key;
    string word,meaning;
    char color,character;
    Node *parent;
    Node *left;
    Node *right;
};

class RBT
{
    private:
    Node *root;
    Node *firstNode;
    void rotateLeft(Node *rNode);
    void rotateRight(Node *rNode);
    void displayRBT(Node *root,string structure, bool side);
    Node* searchNode(Node *root, int pSearchItem);
    void nodeSetEdges(Node *node, Node *rightNode);
    Node* findMinimumValue(Node *rNode);

    public :
        RBT()
        {
            firstNode = new Node;
            firstNode->color = 'b';
            firstNode->left = NULL;
            firstNode->right = NULL;
            root = firstNode;
        }
        void insert();
        void print();
        void search();
        int deleteNode(char data);
};

void RBT :: insert()
{
    string iWord,iMeaning;

    system("cls");
    decSubTopic("ADD NEW WORD");
    //cin.ignore();
    cout<<"\n\n\n\n\t\t\t\t\t\tEnter the Word: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    getline(cin,iWord);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    //cin.ignore();
    cout<<"\n\t\t\t\t\t\tEnter the Meaning: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    getline(cin,iMeaning);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);

    Node *newNode = new Node;
    newNode->parent = NULL;
    newNode->key = iWord[0];
    newNode->character = iWord[0];
    newNode->word = iWord;
    newNode->meaning = iMeaning;
    newNode->left = firstNode;
    newNode->right = firstNode;
    newNode->color = 'r';

    Node *lastNode = NULL;
    Node *tempNode = root;

    while (tempNode != firstNode) {
      lastNode = tempNode;
      if (newNode->key < tempNode->key) {
        tempNode = tempNode->left;
      } else {
        tempNode = tempNode->right;
      }
    }

    newNode->parent = lastNode;
    if (lastNode == NULL) {
      root = newNode;
    } else if (newNode->key < lastNode->key) {
      lastNode->left = newNode;
    } else {
      lastNode->right = newNode;
    }

//     if (node->parent == NULL) {
//       node->color = 'b';
//       return;
//     }

//     if (node->parent->parent == NULL) {
//       return;
//     }

    Node *grndNode;
    while ((newNode->parent!= NULL) && newNode->parent->color == 'r') {

      if (newNode->parent == newNode->parent->parent->right) {

        grndNode = newNode->parent->parent->left;

        if (grndNode->color == 'r') {
          grndNode->color = 'b';
          newNode->parent->color = 'b';
          newNode->parent->parent->color = 'r';
          newNode = newNode->parent->parent;
        }
        else {

          if (newNode == newNode->parent->left) {

            newNode = newNode->parent;
            rotateRight(newNode);
          }

          newNode->parent->color = 'b';
          newNode->parent->parent->color = 'r';
          rotateLeft(newNode->parent->parent);
        }
      }
      else
      {

        grndNode = newNode->parent->parent->right;

        if (grndNode->color == 'r') {
          grndNode->color = 'b';
          newNode->parent->color = 'b';
          newNode->parent->parent->color = 'r';
          newNode = newNode->parent->parent;
        }
        else
        {

          if (newNode == newNode->parent->right) {
            newNode = newNode->parent;
            rotateLeft(newNode);
          }

          newNode->parent->color = 'b';
          newNode->parent->parent->color = 'r';
          rotateRight(newNode->parent->parent);
        }

      }
      if (newNode == root) {
        break;
      }
    }
    root->color = 'b';
}

void RBT :: rotateLeft(Node *rNode)
{
    Node *tempRotate = rNode->right;
    rNode->right = tempRotate->left;

    if(tempRotate->left != NULL)
        tempRotate->left->parent = rNode;

    tempRotate->parent = rNode->parent;

    if(rNode->parent == NULL)
        root = tempRotate;
    else if(rNode->parent->left == rNode)
        rNode->parent->left = tempRotate;
    else
        rNode->parent->right = tempRotate;

    tempRotate->left = rNode;
    rNode->parent = tempRotate;
}

void RBT :: rotateRight(Node *rNode)
{
    Node *tempRotate = rNode->left;
    rNode->left = tempRotate->right;

    if(tempRotate->right != NULL)
        tempRotate->right->parent = rNode;

    tempRotate->parent = rNode->parent;

    if(rNode->parent == NULL)
        root = tempRotate;
    else if(rNode->parent->right == rNode)
        rNode->parent->right = tempRotate;
    else
        rNode->parent->left = tempRotate;

    tempRotate->right = rNode;
    rNode->parent = tempRotate;
}

Node* RBT :: searchNode(Node *root, int pSearchItem)
{
    if(root == firstNode || root->key == pSearchItem)
      return root;
    else if(root->key > pSearchItem)
      return searchNode(root->left,pSearchItem);
    else
      return searchNode(root->right,pSearchItem);
}

void RBT :: search()
{
    string iWord;

    system("cls");
    decSubTopic("SEARCH MEANING");
    //cin.ignore();
    cout<<"\n\n\n\n\t\t\t\t\t\tEnter the Word: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    getline(cin,iWord);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    //cin.ignore();
    if(searchNode(root,iWord[0]) != firstNode)
    {
      cout<<"\n\t\t\t\t\t\tMeaning: ";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
      cout<<searchNode(root,iWord[0])->meaning<<endl;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    }
    else
    {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
      cout<<"\n\n\n\n\n\n\t\t\t\t\t\t\tcannot find data";
    }

    cout<<"\n\n\t\t\t\t\t\tPress Enter Any key to return main menu......";
    getch();
}

void RBT :: nodeSetEdges(Node *node, Node *rightNode)
{
    if (node->parent == NULL)
      root = rightNode;
    else if (node == node->parent->left)
      node->parent->left = rightNode;
    else
      node->parent->right = rightNode;

    rightNode->parent = node->parent;
}

Node* RBT :: findMinimumValue(Node *rNode)
{
  while (rNode->left != firstNode)
    rNode = rNode->left;
  return rNode;
}

int RBT :: deleteNode(char data)
{
    Node *tempNOde,*delTemp,*delNode = searchNode(root,data);

    if(delNode == firstNode)
      return 0;

    delTemp = delNode;
    char delNodeColor = delTemp->color;

    if(delNode->left == firstNode)
    {
      tempNOde = delNode->right;
      nodeSetEdges(delNode,delNode->right);
    }
    else if (delTemp->right == firstNode)
    {
      tempNOde = delNode->left;
      nodeSetEdges(delNode, delNode->left);
    }
    else
    {
      delTemp = findMinimumValue(delNode->right);
      delNodeColor = delTemp->color;
      tempNOde = delTemp->right;
      if (delTemp->parent == delNode)
        tempNOde->parent = delTemp;
      else
      {
        nodeSetEdges(delTemp, delTemp->right);
        delTemp->right = delNode->right;
        delTemp->right->parent = delTemp;
      }

      nodeSetEdges(delNode, delTemp);
      delTemp->left = delNode->left;
      delTemp->left->parent = delTemp;
      delTemp->color = delNode->color;
    }

    delete delNode;
    Node *siblingNode;
    if (delNodeColor == 'b')
    {
        while (tempNOde != root && tempNOde->color == 'b')
        {
          if (tempNOde == tempNOde->parent->left)
          {

            siblingNode = tempNOde->parent->right;
            if (siblingNode->color == 'r')
            {
              siblingNode->color = 'b';
              tempNOde->parent->color = 'r';
              rotateLeft(tempNOde->parent);
              siblingNode = tempNOde->parent->right;
            }

            if (siblingNode->left->color == 'b' && siblingNode->right->color == 'b')
            {
              siblingNode->color = 'r';
              tempNOde = tempNOde->parent;
            }
            else
            {
              if (siblingNode->right->color == 'b')
              {
                siblingNode->left->color = 'b';
                siblingNode->color = 'r';
                rotateRight(siblingNode);
                siblingNode = tempNOde->parent->right;
              }

              siblingNode->color = tempNOde->parent->color;
              tempNOde->parent->color = 'b';
              siblingNode->right->color = 'b';
              rotateLeft(tempNOde->parent);
              tempNOde = root;
            }


          }
          else
          {

            siblingNode = tempNOde->parent->left;
            if (siblingNode->color == 'r')
            {
              siblingNode->color = 'b';
              tempNOde->parent->color = 'r';
              rotateRight(tempNOde->parent);
              siblingNode = tempNOde->parent->left;
            }

            if (siblingNode->right->color == 'b' && siblingNode->right->color == 'b')
            {
              siblingNode->color = 'r';
              tempNOde = tempNOde->parent;
            }
            else
            {
              if (siblingNode->left->color == 'b')
              {
                siblingNode->right->color = 'b';
                siblingNode->color = 'r';
                rotateLeft(siblingNode);
                siblingNode = tempNOde->parent->left;
              }

              siblingNode->color = tempNOde->parent->color;
              tempNOde->parent->color = 'b';
              siblingNode->left->color = 'b';
              rotateRight(tempNOde->parent);
              tempNOde = root;
            }

          }
      }
      tempNOde->color = 'b';
    }

}

void RBT :: displayRBT(Node *root,string structure, bool side)
{
    int color;
    if(root != firstNode)
    {
        cout<<structure;
        if(side)
        {
            cout<<"R-----";
            structure += "    ";
        }
        else{
            cout<<"L-----";
            structure +="|   ";
        }

        color = root->color == 'r' ? 4 : 7;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
        cout<<root->character<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        displayRBT(root->left,structure,false);
        displayRBT(root->right,structure,true);
    }
}

void RBT :: print()
{
    displayRBT(root,"",true);
}

void decoration()
{
  cout<<"\t\t\t\t\t\t\t\t\t       @@     @@@@@@  ";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
  cout<<" @@   @@  @@@@@@@   @@@@@@"<<endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
  cout<<"\t\t\t\t\t\t\t\t\t       @@     @@      ";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
  cout<<"  @@ @@     @@     @@"<<endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
  cout<<"\t\t\t\t\t\t\t\t\t       @@     @@@@    ";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
  cout<<"   @@       @@     @@@@@@"<<endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
  cout<<"\t\t\t\t\t\t\t\t\t       @@     @@      ";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
  cout<<"  @@ @@     @@          @@"<<endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
  cout<<"\t\t\t\t\t\t\t\t\t       @@@@@  @@@@@@  ";
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
  cout<<" @@   @@  @@@@@@@  @@@@@@"<<endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

void LoadingBar()
{
    gotoxy(2,1);
    char des=219;
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    decoration();
    cout<<endl<<endl;
    gotoxy(90,24);
    cout<<"PLEASE WAIT...";
    gotoxy(79,21);
    cout<<"loading...";
    for(int j=0;j<=100;j++)
    {
        gotoxy(0,21);
        cout<<"\n\t\t\t\t\t\t\t\t\t       ";
        for(int i=1;i<=33;i++)
          cout<<des;
        cout<<endl;
    }
    for(int j=0;j<=100;j++)
    {
        gotoxy(115,22);
        cout<<j<<"%"<<endl;
        gotoxy(0,21);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
        cout<<"\n\t\t\t\t\t\t\t\t\t       ";
        for(int i=1;i<=j;i++)
        {
            if(i%3==0)
            {
                cout<<des;
            }
        }
        cout<<endl;
        Sleep(70);
    }
    Sleep(4000);
}

int main()
{
    LoadingBar();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    RBT obj;
    string dlWord;
    do
    {
      system("cls");

      cout<<endl<<endl<<endl;
      decoration();
      gotoxy(78,9);
      cout<<"The road map of the culture, feed your mind "<<endl;
      gotoxy(90,10);
      cout<<"with language..."<<endl;

      gotoxy(78,15);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
      cout<<q<<q<<q<<q<<q<<q;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
      cout<<q<<q<<q<<q<<q<<q<<q;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
      cout<<q<<q<<q;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
      cout<<" MAIN MENU " ;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
      cout<<q<<q<<q;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
      cout<<q<<q<<q<<q<<q<<q<<q;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
      cout<<q<<q<<q<<q<<q<<q;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
      gotoxy(78,19);
      cout<<g<<g<<g<<g<<q<<" 1. ADD WORD   ";
      gotoxy(78,21);
      cout<<g<<g<<g<<g<<q<<" 2. SEARCH WORD";
      gotoxy(78,23);
      cout<<g<<g<<g<<g<<q<<" 3. DELETE WORD";
      gotoxy(78,25);
      cout<<g<<g<<g<<g<<q<<" 4. VIEW DICTIONARY";
      gotoxy(78,27);
      cout<<g<<g<<g<<g<<q<<" 0. EXIT";
      gotoxy(78,29);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
      cout<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine<<underLine;
      gotoxy(78,31);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
      cout<<"Enter your choice: ";
      switch(getch())
      {
          case '1':
            system("cls");
            obj.insert();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
            cout<<"\n\n\n\n\t\t\t\t\t\t\tnode Inserted.\n\n\n\t\t\t\t\t\tPress Enter Any key to return main menu......";
            getch();
            break;
          case '2':
            obj.search();
            break;
          case '3':
            system("cls");
            decSubTopic("DELETE WORD");
            //cin.ignore();
            cout<<"\n\n\n\n\t\t\t\t\t\tEnter the Word: ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
            getline(cin,dlWord);
            if(obj.deleteNode(dlWord[0]))
              cout<<"\n\n\n\n\t\t\t\t\t\t\tDeleted success\n\n\t\t\t\t\t\tPress Enter Any key to return main menu......";
            else
              cout<<"\n\n\n\n\t\t\t\t\t\t\tcannot find data\n\n\t\t\t\t\t\tPress Enter Any key to return main menu......";

            getch();
            break;
          case '4':
            system("cls");
            decSubTopic("Dictionary View as a Tree View",0,5);
            cout<<endl<<endl<<endl;
            obj.print();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
            cout<<"\n\n\nPress Enter Any key to return main menu......";
            getch();
            break;
          case '0':
            system("cls");
                gotoxy(23,7);
                cout<<"Are You sure!!!!\n\t\t\t\tThen Press";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                cout<<" (y) ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                cout<<"or ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                cout<<"(n)...";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                switch(getch())
                {
                case 'y':
                case 'Y':
                    system("cls");
                    gotoxy(20,6);
                    cout<<"PROGRAMMERS....";
                    gotoxy(20,9);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                    cout<<"1. Sachintha Madhawa         MA-HDSE-202-F-004";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
                    Sleep(1000);
                    gotoxy(20,10);
                    cout<<"   E-mail: hdsema202f004@student.nibm.lk";
                    gotoxy(50,13);
                    Sleep(1000);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                    cout<<"...................THANK YOU...................";
                    gotoxy(50,16);
                    cout<<"Exiting in 5 second...........";
                    Sleep(5000);
                    system("cls");
                    exit(0);
                    break;
                }
            break;
          default:
            cout<<"\nEnter a Valid Choice.";
            break;
      }

    }while(true);
    return 0;
}
