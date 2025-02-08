#include <iostream>
#include <cstdlib> 
#include <cstring> // for comparing

struct Book
{
    char title[100];
    char author[100];
    char isbn[20];
    int available;
};

void addBook(Book** lib, int* size, int* n) 
{
    if(*size >= *n)   // if libriary size >= library memory increase capacity
    {
        *n = (*n) * 2;
        *lib = (Book*)realloc(*lib, (*n) * sizeof(Book));
    }
    std::cout<<"Enter title, author and isbn"<<std::endl;
    std::cin.ignore(); 
    std::cin.getline((*lib)[*size].title, 100);
    std::cin.getline((*lib)[*size].author, 100);
    char test[20];   //test for isbn input
    bool flag=true;
    while(flag)
    {
        flag=false;
        std::cin.getline(test, 20);   //input of isbn version
        for(int i=0; i<(*size); ++i)
        {
            if(strcmp(test, (*lib)[i].isbn) == 0)    // if the version exists try again
            {
                std::cout<<"Try again"<<std::endl;
                flag=true;
                break;
            }        
        }
        if(!flag)   // if the version is new
        {
            for(int i=0; ; ++i)
            {
                if(test[i] == '\0')
                {
                    break;
                }
                (*lib)[*size].isbn[i]=test[i];  // accept the version
            }
        }
    }
    (*lib)[*size].available=1;
    ++(*size);  
}

void listBooks(Book* lib, const int size)
{
    std::cout<<"List of books"<<std::endl;
    for(int i=0; i<size; ++i)
    {
        std::cout<<lib[i].title<<" "<<lib[i].author<<" "<<lib[i].isbn<<" "<<lib[i].available<<std::endl;
    }
}

void searchBook(Book* lib, const int size, char* sp)
{
    bool flag=false;
    for(int i=0; i<size; ++i)
    {
        if (strcmp(lib[i].title, sp) == 0 || strcmp(lib[i].author, sp) == 0)    //if such an author or title exists, output the data for that book
        {
            flag=true;
            std::cout<<lib[i].title<<" "<<lib[i].author<<" "<<lib[i].isbn<<" "<<lib[i].available<<std::endl;
            break;
        }
    }
    if(!flag)
    {
        std::cout<<"The book is not found"<<std::endl;
    }
}

void borrowBook(Book* lib, const int size, char* index)
{
    bool flag=false;
    for(int i=0; i<size; ++i)
    {
        if(strcmp(lib[i].isbn, index) == 0 && lib[i].available == 1)    // if there is such a book, and it is available
        {
            flag=true;
            lib[i].available=0;
            break;
        }
        else if(strcmp(lib[i].isbn, index) == 0 && lib[i].available == 0)   // if there is such a book, and it is not available
        {
            flag=true;
            std::cout<<"The book is missing from the library."<<std::endl;
            break;
        }
    }
    if( !flag )
    {
        std::cout<<"The book is not found"<<std::endl;
    }
}

void returnBook(Book* lib, const int size, char* index)
{
    bool flag=false;
    for(int i=0; i<size; ++i)
    {
        if(strcmp(lib[i].isbn, index) == 0 && lib[i].available == 0)    // if there is such a book, and it is not available
        {
            flag=true;
            lib[i].available=1;
            break;
        }
        else if(strcmp(lib[i].isbn, index) == 0 && lib[i].available == 1)   // if there is such a book, and it is available
        {
            flag=true;
            std::cout<<"The book is not missing from the library."<<std::endl;
            break;
        }
    }
    if( !flag )
    {
        std::cout<<"The book is not found"<<std::endl;
    }
}

int main()
{
    int n=0;
    int size=0;
    std::cout<<"Input count of books"<<std::endl;
    std::cin>>n;
    size=n;
    Book* lib=(Book*)malloc(n*(sizeof(Book)));
    std::cout<<"Enter itle, author and ISBN for "<<n<<" books"<<std::endl;
    for(int i=0; i<n; ++i)
    {
        std::cin>>lib[i].title>>lib[i].author>>lib[i].isbn;
        lib[i].available=1;
    }
    char t[10]; // for option input
    std::cout<<"input option (add , list , search , borrow , return or exit)"<<std::endl;
    std::cin>>t;
    while (strcmp(t, "exit") != 0)
    {
        if(strcmp(t, "add") == 0)
        {
            addBook(&lib, &size, &n);
        }
        else if(strcmp(t, "list") == 0)
        {
            listBooks(lib,size);
        }
        else if(strcmp(t, "search") == 0)
        {
            char sp[30];    // searching author or title
            std::cin.ignore();
            std::cin.getline(sp, 100);
            searchBook(lib, size, sp);
        }
        else if(strcmp(t, "borrow") == 0)
        {
            char index[20];     // searching isbn
            std::cout<<"Input book's ISBN"<<std::endl;
            std::cin>>index;
            borrowBook(lib, size, index);
        }
        else if(strcmp(t, "return") == 0)
        {
            char index[20];     // searching isbn
            std::cout<<"Input book's ISBN"<<std::endl;
            std::cin>>index;
            returnBook(lib, size, index);
        }
        else
        {
            break;
        }
        std::cout<<"input option (add , list , search , borrow , return or exit)"<<std::endl;
        std::cin>>t;        // next option
    }
    if(strcmp(t, "exit") == 0)
    {
        std::cout<<"End of the program"<<std::endl;
    }
    else
    {
        std::cout<<"Wrong input!!!"<<std::endl;
    }
    free(lib);
    return 0;
}


