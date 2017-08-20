#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void readSpaces(FILE *fp);
void writeSpaces(FILE * fp,int nb);
void readString(FILE *fp,FILE *fp1);
void readMultiComment(FILE *fp,FILE *fp1,int nb);
void readSingleComment(FILE *fp,FILE *fp1,int nb);
void readShortString(FILE *fp,FILE *fp1);

//no.of spaces
int sp;

int main(int argc, char* argv[])
{
    int nb=0;
    FILE *fp,*fp1;
    char name[20],t = '\0',c;

    if(argc == 2)
    {
        fp = fopen(argv[1],"r");
        sp = 4;
    }
    else if(argc == 3)
    {
        fp = fopen(argv[1],"r");
        sp = atoi(argv[2]);
    }
    else
    {
        cout << "Enter the File Name : ";
        gets(name);
        cout << "Enter the no. of spaces you want to give : ";
        cin >> sp;
        fp = fopen(name,"r");
    }

    fp1 = fopen("temp.txt","w");
    if(fp == NULL || fp1 == NULL)
    {
        cout << "Can't Open the File\nTerminating!!";
        getch();
        return 0;
    }

    c = fgetc(fp);
    while (!feof(fp))
    {
        if(c == '{')
        {
            if(t != '\n')
            {
                fputc('\n',fp1);
                writeSpaces(fp1,nb);
            }
            ++nb;
            c=fgetc(fp);
            if(c != '\n')
            {
                fputc('{',fp1);
                c = '\n';
                fseek(fp,-1,1);
            }
            else
            {
                fseek(fp,-1,1);
                c = '{';
            }
        }
        if(c == '}')
        {
            --nb;
            if(t == '\n')
            {
                fseek(fp1,-sp,1);
            }
            else
            {
                fputc('\n',fp1);
                writeSpaces(fp1,nb);
            }
        }
        fputc(c,fp1);
        if(c == '\n')
        {
            readSpaces(fp);
            writeSpaces(fp1,nb);
        }
        if(c == '/' && t == '/')
            readSingleComment(fp,fp1,nb);
        if(c == '*' && t == '/')
            readMultiComment(fp,fp1,nb);
        t=c;
        if(c == '\'')
            readShortString(fp,fp1);
        if(c == '"')
            readString(fp,fp1);
        c = fgetc(fp);
    }
    fclose(fp);
    fclose(fp1);
    cout << "\nIndentation successful";
    cout << "\nIndented File have been saved as temp.txt";
    getche();
    //remove(name);
    //rename("temp.txt",name);
    return 0;
}

void readSpaces(FILE *fp)
{
    char c;
    c = fgetc(fp);
    if(!feof(fp))
    {
        while((c == ' ' || c == '\t') && !feof(fp))
        {
            c = fgetc(fp);
        }
        fseek(fp,-1,1);
    }
}

void writeSpaces(FILE *fp,int nb)
{
    for(int i = 0; i < sp*nb; ++i)
        fprintf(fp," ");
}

void readString(FILE *fp,FILE *fp1)
{
    char c = '\0';
    while(c!='"')
    {
        c = fgetc(fp);
        fputc(c,fp1);
    }
}

void readShortString(FILE *fp,FILE *fp1)
{
    char c = '\0';
    while(c!='\'')
    {
        c = fgetc(fp);
        fputc(c,fp1);
    }
    c = fgetc(fp);
    if(c=='\'')
    {
        fputc(c,fp1);
    }
    else
    {
        fseek(fp,-1,1);
    }
}

void readMultiComment(FILE *fp,FILE *fp1,int nb)
{
    char c = '\0';
    while(!feof(fp))
    {
        c = fgetc(fp);
        fputc(c,fp1);
        if(c == '\n')
        {
            readSpaces(fp);
            writeSpaces(fp1,nb);
        }
        if(c == '*')
        {
            c = fgetc(fp);
            if(c == '/')
            {
                putc(c,fp1);
                break;
            }
        }
    }
}

void readSingleComment(FILE *fp,FILE *fp1,int nb)
{
    char c = '\0';
    while(c!='\n')
    {
        c = fgetc(fp);
        fputc(c,fp1);
    }
    readSpaces(fp);
    writeSpaces(fp1,nb);
}
