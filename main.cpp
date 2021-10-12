#include <iostream>
#include <cstring>
#include <fstream>
#include <graphics.h>
using namespace std;
///
///captarea dimensiunii ecranului
int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);
int x1,y1;///coordonatele click ului
int window1=initwindow(Width,Height,"Derivare Formala");
//int nr_nod;
///
char expresie[100],expresie_finala[200];
char operatorr[30][5];

struct arbore
{
    char info[5];
    arbore *stg, *dr;
};
struct vectorx
{
    char info[100][5];
    int maxim;

};


char expresia[100],expresia2[100];
vectorx vectorul;
arbore *arborele, *arborele_derivat;
///
void inserare(char expr[100],char c)
{
    int i;
    int n=strlen(expr);
    int poz=n-2;
    for(i=n; i>=poz; i--)
        expr[i+1]=expr[i];
    n++;
    expr[poz]=c;
}
///grafica


///

int verifica_baza (char s[100])
{
    int ok=1;
    int i;
    for(i=0; i<strlen(s); i++)
        if(!(s[i]>=48 && s[i]<=57))
            ok=0;
    if(ok==1)
        return 1;
    return 0;
}

void Vectorizeaza(char expr[100], vectorx &vec)
{
    char c[2];
    c[1] = NULL;
    int i = 0, j, k = 0;
    while (i<strlen(expr))
    {
        if (strchr("slt", expr[i]) || (strchr("c",expr[i])&& strchr("o",expr[i+1])) ||
                (strchr("c",expr[i])&& strchr("t",expr[i+1])))
        {
            {
                c[0] = expr[i];
                strcat(vec.info[k], c);
                c[0] = expr[i + 1];
                strcat(vec.info[k], c);
                c[0] = expr[i + 2];
                strcat(vec.info[k], c);
                k++;
            }

            {
                c[0] = expr[i + 2];
                strcat(vec.info[k], c);
                i = i + 2;
            }


        }
        else if (strchr("()+/-*^x", expr[i]))
        {
            c[0] = expr[i];
            strcpy(vec.info[k], c);
            k++;
        }
        else
        {
            strcpy(vec.info[k], "");
            while (!(strchr("()+-*^/scle", expr[i])))
            {
                c[0] = expr[i];
                strcat(vec.info[k], c);
                i++;
            }
            k++;
            i--;
        }
        i++;


    }
    vec.maxim = k;

}
int prioritate(char op)
{
    if (op == '(' || op == ')')
        return 0;
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    if (strchr("scle", op))
        return 4;
}


void Arborizeaza(vectorx vec, arbore *&arb)
{
    int i, top1, top2;
    char operatorr[30][5];
    arbore *operand[30];

    i = 0;
    top1 = 0;
    top2 = 1;
    strcpy(operatorr[0], "(");

    while (i <= vec.maxim && top2>=0)
    {

        if (strchr("x0123456789", vec.info[i][0]))
        {

            arb = new arbore;
            strcpy(arb->info, vec.info[i]);
            arb->stg = NULL;
            arb->dr = NULL;
            operand[top1] = arb;
            top1++;
        }
        else if (vec.info[i][0] == '(')
        {
            strcpy(operatorr[top2], "(");
            top2++;
        }
        else
        {

            while ((top2>0) && (operatorr[top2-1][0]!='(') && (operatorr[top2-1][0]!=')') &&
                    (prioritate(operatorr[top2-1][0]) >= prioritate(vec.info[i][0])))
            {


                top2--;
                if (strchr("s", operatorr[top2][0]) || (strchr("c",operatorr[top2][0]) && strchr("o",operatorr[top2][1]))
                        || (strchr("c",operatorr[top2][0]) && strchr("t",operatorr[top2][1])))
                {
                    arb = new arbore;
                    strcpy(arb->info, operatorr[top2]);
                    arb->stg =operand[top1-1] ;
                    arb->dr = NULL;
                    operand[top1-1] = arb;
                }
                else if((strchr("t",operatorr[top2][0]) && strchr("a",operatorr[top2][1])))
                {
                    arb = new arbore;
                    strcpy(arb->info, operatorr[top2]);
                    arb->stg =NULL;
                    arb->dr = operand[top1-1];
                    operand[top1-1] = arb;
                }
                else
                {
                    top1--;
                    arb = new arbore;
                    strcpy(arb->info, operatorr[top2]);
                    arb->stg = operand[top1-1];
                    arb->dr = operand[top1];
                    operand[top1-1] = arb;
                }
            }

            if (top2>0)

                if (operatorr[top2-1][0]!='(' || vec.info[i][0] != ')')
                {

                    strcpy(operatorr[top2], vec.info[i]);
                    top2++;

                }
                else
                    top2--;

        }

        i++;

    }


    if (i-1 == vec.maxim )
    {
        arb = new arbore;
        arb = operand[0];
    }
}

void Deriveaza(arbore *arbi, arbore *&arb)
{
    arbore *arb1, *arb2, *arb3, *arb4, *arb5, *arb6, *arb7;
    arb = new arbore;
    strcpy(arb->info, "false");
    arb->stg = NULL;
    arb->dr = NULL;
    if(arbi->info[0]=='0')
        strcpy(arb->info, "0");
    if(arbi->info[0]=='1')
        strcpy(arb->info, "0");
    if(arbi->info[0]=='2')
        strcpy(arb->info, "0");
    if(arbi->info[0]=='3')
        strcpy(arb->info, "0");
    if(arbi->info[0]=='4')
        strcpy(arb->info, "0");
    if(arbi->info[0]=='5')
        strcpy(arb->info, "0");
    if(arbi->info[0]=='6')
        strcpy(arb->info, "0");
    if(arbi->info[0]=='7')
        strcpy(arb->info, "0");
    if(arbi->info[0]=='8')
        strcpy(arb->info, "0");
    if(arbi->info[0]=='9')
        strcpy(arb->info, "0");
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(arbi->info[0]=='x')
        strcpy(arb->info, "1");
    if(arbi->info[0]=='+')
    {
        Deriveaza(arbi->stg, arb3);
        arb->stg = arb3;
        Deriveaza(arbi->dr, arb4);
        arb->dr = arb4;
        strcpy(arb->info, "+");
    }
    if(arbi->info[0]=='-')
    {
        Deriveaza(arbi->stg, arb3);
        arb->stg = arb3;
        Deriveaza(arbi->dr, arb4);
        arb->dr = arb4;
        strcpy(arb->info, "-");
    }
    if(arbi->info[0]=='*')
    {
        arb1 = new arbore;
        arb2 = new arbore;
        Deriveaza(arbi->stg, arb3);
        Deriveaza(arbi->dr, arb4);
        strcpy(arb->info, "+");
        arb1->stg = arb3;
        arb1->dr = arbi->dr;
        strcpy(arb1->info, "*");
        arb2->stg = arbi->stg;
        arb2->dr = arb4;
        strcpy(arb2->info, "*");
        arb->stg = arb1;
        arb->dr = arb2;
    }
    if(arbi->info[0]=='/')
    {

        strcpy(arb->info,"/");
        ///g^2=arb1
        arb1=new arbore;
        strcpy(arb1->info,"^");
        arb1->stg=arbi->dr;
        arb1->dr=new arbore;
        strcpy(arb1->dr->info,"2");
        arb1->dr->dr=NULL;
        arb1->dr->stg=NULL;
        ///arb2 = f'*g
        arb2=new arbore;
        strcpy(arb2->info,"*");
        arb2->dr=arbi->dr;
        Deriveaza(arbi->stg,arb5);
        arb2->stg=arb5;
        ///arb3=f*g'
        arb3=new arbore;
        strcpy(arb3->info,"*");
        arb3->stg=arbi->stg;
        Deriveaza(arbi->dr,arb6);
        arb3->dr=arb6;
        ///arb4 -
        arb4=new arbore;
        strcpy(arb4->info,"-");
        arb4->stg=arb2;
        arb4->dr=arb3;
        arb->stg=arb4;
        arb->dr=arb1;
        /////////////////////////////////////////////

    }
    if(arbi->info[0]=='s' && arbi->info[1]=='i' && arbi->info[2]=='n')
    {
        //cout<<"sin"<<endl;
        arb1 = new arbore;
        strcpy(arb1->info, "cos");
        arb1->stg = arbi->stg;
        arb1->dr = NULL;
        Deriveaza(arbi->stg, arb2);
        strcpy(arb->info, "*");
        arb->stg = arb1;
        arb->dr = arb2;
    }

    if(arbi->info[0]=='c' && arbi->info[1]=='o' &&  arbi->info[2]=='s')
    {
        ///

        //cout<<arbi->stg->info<<" "<<arb->dr->info;
        strcpy(arb->info,"*");
        Deriveaza(arbi->stg,arb1);
        ///
        arb3=new arbore;
        strcpy(arb3->info,"sin");
        arb3->dr=NULL;
        arb3->stg=arbi->stg;
        arb2=new arbore;
        strcpy(arb2->info,"*");
        ///
        arb4=new arbore;
        strcpy(arb4->info,"-1");
        arb4->dr=NULL;
        arb4->stg=NULL;
        ///
        ///
        arb2->dr=arb3;
        arb2->stg=arb4;
        arb->dr=arb1;
        arb->stg=arb2;

        ///
    }
    ///logaritmica
    if(arbi->info[0]=='l' && arbi->info[1]=='o' && arbi->info[2]=='g')
    {
        ///arb
        ///
        arb4=new arbore;
        strcpy(arb4->info,"ln");
        arb4->dr=NULL;
        arb4->stg=NULL;
        strcpy(arb->info, "*");
        arb2=new arbore;
        strcpy(arb2->info,"/");
        arb2->stg=new arbore;
        arb2->stg->dr=NULL;
        arb2->stg->stg=NULL;
        strcpy(arb2->stg->info,"1");
        ///arb3
        arb3=new arbore;
        strcpy(arb3->info,"*");
        arb3->stg=arbi->dr;
        arb3->dr=new arbore;
        strcpy(arb3->dr->info,"ln");
        strcat(arb3->dr->info,arbi->stg->info);
        arb3->dr->dr=NULL;
        arb3->dr->stg=NULL;
        ///legaturi
        arb2->dr=arb3;

        ///
        Deriveaza(arbi->dr, arb1);
        arb->dr = arb1;
        arb->stg=arb2;
    }

    ///tangenta
    if(arbi->info[0]=='t' && arbi->info[1]=='a' && arbi->info[2]=='n')
    {
        arb2=new arbore;
        Deriveaza(arbi->dr,arb1);
        ///cos^2
        strcpy(arb->info,"*");
        strcpy(arb2->info,"cos");
        arb2->dr=NULL;
        arb2->stg=arbi->dr;
        ///arb3
        arb3=new arbore;
        strcpy(arb3->info,"^");
        arb3->stg=arb2;
        arb3->dr=new arbore;
        strcpy(arb3->dr->info,"2");
        arb3->dr->dr=NULL;
        arb3->dr->stg=NULL;
        ///arb4
        arb4=new arbore;
        strcpy(arb4->info,"/");
        arb4->dr=arb3;
        arb4->stg=new arbore;
        strcpy(arb4->stg->info,"1");
        arb4->stg->dr=NULL;
        arb4->stg->stg=NULL;
        arb->stg=arb4;
        arb->dr=arb1;
    }

    ///cotangenta
    if(arbi->info[0]=='c' && arbi->info[1]=='t' && arbi->info[2]=='g')
    {
        Deriveaza(arbi->stg,arb1);
        strcpy(arb->info,"*");
        arb2=new arbore;
        strcpy(arb2->info,"sin");
        arb2->dr=NULL;
        arb2->stg=arbi->stg;
        ///arb3
        strcpy(arb3->info,"^");
        arb3->stg=arb2;
        arb3->dr=new arbore;
        strcpy(arb3->dr->info,"2");
        arb3->dr->dr=NULL;
        arb3->dr->stg=NULL;
        ///arb4
        arb4=new arbore;
        strcpy(arb4->info,"/");
        arb4->dr=arb3;
        arb4->stg=new arbore;
        strcpy(arb4->stg->info,"-1");
        arb4->stg->dr=NULL;
        arb4->stg->stg=NULL;

        arb->stg=arb4;
        arb->dr=arb1;
    }
    ///exponentiala
    if(arbi->info[0]=='^' && (verifica_baza(arbi->stg->info)))
    {
        strcpy(arb->info,"*");
        Deriveaza(arbi->dr,arb1);
        arb3=new arbore;
        strcpy(arb3->info,"ln");
        strcat(arb3->info,arbi->stg->info);
        arb3->dr=NULL;
        arb3->stg=NULL;
        ///
        arb2=new arbore;
        strcpy(arb2->info,"*");
        arb2->stg=arbi;
        arb2->dr=arb3;
        arb->stg=arb2;
        arb->dr=arb1;
    }
    ///putere
    if(arbi->info[0]=='^' && !(verifica_baza(arbi->stg->info)))
    {
        //cout<<endl<<"putere"<<endl;
        ///bun
        char s[10];
        Deriveaza(arbi->stg,arb1);
        strcpy(arb->info,"*");
        arb2=new arbore;
        strcpy(arb2->info,"^");
        arb2->stg=arbi->stg;
        ////
        strcpy(s,arbi->dr->info);
        int i=atoi(s);
        i--;
        itoa(i,s,10);
        ///
        arb2->dr=new arbore;
        strcpy(arb2->dr->info,s);
        arb2->dr->dr=NULL;
        arb2->dr->stg=NULL;
        ///arb3
        arb3=new arbore;
        strcpy(arb3->info,"*");
        arb3->dr=arb2;
        arb3->stg=arbi->dr;
        ///
        arb->dr=arb1;
        arb->stg=arb3;
    }
}
///parcurgerea arborelui



void parcurgereInOrdine(arbore *arb)
{
    if (arb != NULL)
    {
        if(strchr("sct",arb->info[0]))
        {
            cout <<arb->info<<'(';
            strcat(expresie_finala,arb->info);
            strcat(expresie_finala,"(");
            parcurgereInOrdine(arb->stg);
            cout<<')';
            strcat(expresie_finala,")");
        }
        else if(strchr ("0987654321xpe", arb->info[0]))
            {cout<<arb->info;
            strcat(expresie_finala,arb->info);}
        else
            if(arb->info[0]=='-'&&strchr("0987654321xpe",arb->info[1])&&(arb->dr==NULL||arb->stg==NULL))
                 {cout<<'('<<arb->info<<')';
                 strcat(expresie_finala,"(");
                 strcat(expresie_finala,arb->info);
                 strcat(expresie_finala,")");
                 }
        else

            if (arb->info[0]=='+')
            {
                if(arb->stg->info[0]=='0')
                {

                    if (arb->dr->info[0]!='0')
                        parcurgereInOrdine(arb->dr);
                        else
                        {
                            cout<<'0';
                            strcat(expresie_finala, "0");
                        }
                }

                else
                {
                    parcurgereInOrdine(arb->stg);


                    if(arb->dr->info[0]!='0')
                    {
                        if(arb->stg->info[0]!='0')
                            {cout<<arb->info;
                            strcat(expresie_finala,arb->info);
                            }
                        parcurgereInOrdine(arb->dr);
                    }


                }
            }
            else

                if (arb->info[0]=='-')
                {
                    if(arb->stg->info[0]=='0')
                    {

                        if (arb->dr->info[0]!='0')
                        {
                            cout<<"-";
                            strcat(expresie_finala,"-");
                            parcurgereInOrdine(arb->dr);

                        }
                        else
                        {
                            cout<<'0';
                            strcat(expresie_finala, "0");
                        }

                    }
                    else
                    {
                        parcurgereInOrdine(arb->stg);

                        if(arb->dr->info[0]!='0')
                        {
                            if(arb->stg->info[0]!='0')
                                {cout<<arb->info;
                                strcat(expresie_finala,arb->info);
                                }
                            parcurgereInOrdine(arb->dr);
                        }

                    }
                }
                else if (arb->info[0]=='*')
                {
                    if(arb->stg->info[0]=='0'||arb->dr->info[0]=='0')
                    {
                        cout<<'0';
                        strcat(expresie_finala,"0");
                    }
                    else if(arb->stg->info[0]=='1')
                        parcurgereInOrdine(arb->dr);


                    else
                    {
                        if(arb->dr->info[0]=='1')
                            parcurgereInOrdine(arb->stg);
                        else
                        {
                            if(arb->stg->stg==NULL)
                                parcurgereInOrdine(arb->stg);
                            else
                            {
                                cout<<'(';
                                strcat(expresie_finala,"(");
                                parcurgereInOrdine(arb->stg);
                                cout<<')';
                                strcat(expresie_finala,")");
                            }
                            cout<<arb->info;
                            strcat(expresie_finala,arb->info);
                            if(arb->dr->stg==NULL)
                                parcurgereInOrdine(arb->dr);
                            else
                            {
                                cout<<'(';
                                strcat(expresie_finala,"(");
                                parcurgereInOrdine(arb->dr);
                                cout<<')';
                                strcat(expresie_finala,")");
                            }
                        }

                    }

                }
                else if (arb->info[0]=='/')
                {
                    if(arb->dr->info[0]=='1')
                    {

                        if (arb->stg->info[0]!='1')
                            parcurgereInOrdine(arb->stg);
                    }
                    else
                    {
                        if(arb->dr->info[0]=='0')
                            {cout<<"Expresie incorecta";
                            strcat(expresie_finala,"Expresie incorecta");
                            }
                        else if(arb->stg->info[0]=='0')
                        {
                            cout<<'0';
                            strcat(expresie_finala,"0");
                        }
                        else
                        {
                            if(arb->stg->stg==NULL)
                                parcurgereInOrdine(arb->stg);
                            else
                            {
                                cout<<'(';
                                strcat(expresie_finala,"(");
                                parcurgereInOrdine(arb->stg);
                                cout<<')';
                                strcat(expresie_finala,")");
                            }
                            cout<<arb->info;
                            strcat(expresie_finala,arb->info);
                            if(arb->dr->stg==NULL)
                                parcurgereInOrdine(arb->dr);
                            else
                            {
                                cout<<'(';
                                strcat(expresie_finala,"(");
                                parcurgereInOrdine(arb->dr);
                                cout<<')';
                                strcat(expresie_finala,")");
                            }
                        }



                    }

                }
                else if (arb->info[0]=='^')
                {
                    if(arb->stg->info[0]=='0')
                    {
                        cout<<'0';
                        strcat(expresie_finala,"0");
                    }
                    else if(arb->dr->info[0]=='0')
                    {
                        cout<<'1';
                        strcat(expresie_finala,"1");
                    }
                    else if(arb->stg->info[0]=='1')
                    {
                        cout<<'1';
                        strcat(expresie_finala,"1");
                    }


                    else
                    {
                        if(arb->dr->info[0]=='1')
                            parcurgereInOrdine(arb->stg);
                        else
                        {
                            if(arb->stg->stg==NULL)
                                parcurgereInOrdine(arb->stg);
                            else
                            {
                                cout<<'(';
                                strcat(expresie_finala,"(");
                                parcurgereInOrdine(arb->stg);
                                cout<<')';
                                strcat(expresie_finala,")");
                            }
                            cout<<arb->info;
                            strcat(expresie_finala,arb->info);
                            if(arb->dr->stg==NULL)
                                parcurgereInOrdine(arb->dr);
                            else
                            {
                                cout<<'(';
                                strcat(expresie_finala,"(");
                                parcurgereInOrdine(arb->dr);
                                cout<<')';
                                strcat(expresie_finala,")");
                            }
                        }

                    }


                }
                else if (arb->info[0]=='l')
                {
                    if(arb->info[1]=='n')
                        {cout<<arb->info;
                        strcat(expresie_finala,arb->info);
                        }
                    else
                    {cout<<arb->info;
                    strcat(expresie_finala,arb->info);
                    parcurgereInOrdine(arb->stg);
                    cout<<'(';
                    strcat(expresie_finala,"(");
                    parcurgereInOrdine(arb->dr);
                    cout<<')';
                    strcat(expresie_finala,")");
                    }
                }
                else

                {
                    cout<<'(';
                    strcat(expresie_finala,"(");
                    parcurgereInOrdine(arb->stg);
                    cout<<arb->info;
                    strcat(expresie_finala,arb->info);
                    parcurgereInOrdine(arb->dr);
                    cout<<')';
                    strcat(expresie_finala,")");
                }

    }
}

////////////////////////////////////GRAFICA//////////////////////////////////////////////////
void meniu_grafica ()
{
    int ok=0,okf=1;
    ///
    //int window1=initwindow(Width,Height,"Derivare Formala");
    readimagefile("fundal.jpg",0,0,Width,Height);



    ///
    int L_meniu,l_meniu,dif_l,dif_L,spatiu=10,i,c1,c2;
    L_meniu=Width/4;
    l_meniu=Height/3*2;
    dif_l=Height-l_meniu;
    dif_L=Width-L_meniu;
    dif_l=dif_l/2;

    ///
    setcolor(9);
    settextstyle(10,0,8);
    outtextxy(dif_L,spatiu,"Meniu");
    ///
    ///
    setlinestyle(8,1,2);
    settextstyle(10,0,6);
    setcolor(3);
    circle(Width-(Height-dif_l-dif_l)/9,dif_l/2.3,38);
    setfillstyle(SOLID_FILL,0);
    floodfill(Width-(Height-dif_l-dif_l)/9,dif_l/2.3,9);
    outtextxy(Width-(Height-dif_l-dif_l)/7.1,dif_l/4,"?");

    ///
    setcolor(2);
    setlinestyle(0,1,3);
    ///
    rectangle(Width-spatiu+3,Height-dif_l+3,dif_L-3,dif_l-3);///meniul
    setfillstyle(SOLID_FILL,0);
    floodfill(dif_L+20,dif_l+20,2);
    rectangle(Width-spatiu+3,Height-40,dif_L-3,Height-dif_l+10);///notificari
    float h_patratel=(dif_l-50)/2;
    rectangle(9*spatiu,Height-2*h_patratel,dif_L-10,Height-dif_l+10);///expresie
    rectangle(9*spatiu,Height-h_patratel,dif_L-10,Height-dif_l+10+h_patratel);///derivata
    ///dimensiuni meniu
    int l=Width-spatiu-dif_L;
    int L=Height-dif_l-dif_l;
    ///dimensiuni patratel
    int LL=L/5;
    int ll=l/5;
    ///
    setcolor(5);
    setlinestyle(0,1,3);
    c1=LL;
    for(i=1; i<=5; i++)
    {
        /*setcolor(5);
        setlinestyle(0,1,3);*/
        line(Width-l-10,dif_l+c1,Width-spatiu,dif_l+c1);
        c1=LL*i;
    }
    c2=ll;
    for(i=1; i<=5; i++)
    {
        /*setcolor(5);
        setlinestyle(0,1,3);
        */
        line(Width-l-10+c2,dif_l,Width-l-10+c2, dif_l+L);
        c2=ll*i;

    }

    ///
    setfillstyle(SOLID_FILL,0);
    floodfill(dif_L+15,Height-dif_l+25, 2);
    floodfill(15*spatiu,Height-dif_l+60,2);
    floodfill(15*spatiu,Height-dif_l+20,2);

    ///
    ///pozitionarea tastelor
    setcolor(14);
    settextstyle(8,0,4);
    outtextxy(Width-l-10+ll/2,dif_l+LL/2,"1");
    outtextxy(Width-l-10+ll/2,dif_l+(3*LL)/2,"2");
    outtextxy(Width-l-10+ll/2,dif_l+(5*LL)/2,"3");
    outtextxy(Width-l-10+ll/2,dif_l+(7*LL)/2,"4");
    outtextxy(Width-l-10+ll/2,dif_l+(9*LL)/2,"5");
    ///
    outtextxy(Width-l-10+3*ll/2,dif_l+LL/2,"6");
    outtextxy(Width-l-10+3*ll/2,dif_l+3*LL/2,"7");
    outtextxy(Width-l-10+3*ll/2,dif_l+5*LL/2,"8");
    outtextxy(Width-l-10+3*ll/2,dif_l+7*LL/2,"9");
    outtextxy(Width-l-10+3*ll/2,dif_l+9*LL/2,"0");
    ///
    outtextxy(Width-l-10+5*ll/2-30,dif_l+LL/2,"sin");
    outtextxy(Width-l-10+5*ll/2-30,dif_l+3*LL/2,"cos");
    outtextxy(Width-l-10+5*ll/2-30,dif_l+5*LL/2,"tan");
    outtextxy(Width-l-10+5*ll/2-30,dif_l+7*LL/2,"ctg");
    outtextxy(Width-l-10+5*ll/2-30,dif_l+9*LL/2,"log");
    ///
    outtextxy(Width-l-10+7*ll/2,dif_l+LL/2,"+");
    outtextxy(Width-l-10+7*ll/2,dif_l+3*LL/2,"-");
    outtextxy(Width-l-10+7*ll/2,dif_l+5*LL/2,"*");
    outtextxy(Width-l-10+7*ll/2,dif_l+7*LL/2,"/");
    outtextxy(Width-l-10+7*ll/2,dif_l+9*LL/2,"^");
    ///
    outtextxy(Width-l-10+9*ll/2-30,dif_l+LL/2,"del");
    outtextxy(Width-l-10+9*ll/2,dif_l+3*LL/2,"x");
    outtextxy(Width-l-10+9*ll/2,dif_l+4.1*LL/2,"e");
    outtextxy(Width-l-10+9*ll/2-20,dif_l+5.1*LL/2,"pi");
    outtextxy(Width-l-10+9*ll/2-25,dif_l+7*LL/2,"( )");
    //setcolor(14);
    settextstyle(8,0,1);
    outtextxy(Width-l-10+8.3*ll/2,dif_l+9*LL/2,"E'(x)");
    outtextxy(2*spatiu,Height-dif_l+20,"E(x)=");
    outtextxy(2*spatiu,Height-dif_l+60,"E'(x)=");
    //setcolor(14);

    ///
     setcolor(9);
    settextstyle(10,0,2);
    outtextxy(dif_L+5,Height-dif_l+15,"Pentru indicatii ");
    outtextxy(dif_L+5,Height-dif_l+45,"folositi butonul ? ");
    settextstyle(8,0,4);
    setcolor(14);
    ///coordonate de identificare a butonului
    int l0,l1,l2,l3,l4,l5;
    int L0,L1,L2,L3,L4,L5;
    ///
    l0=Width-l-10;
    l1=l0+ll;
    l2=l1+ll;
    l3=l2+ll;
    l4=l3+ll;
    l5=l4+ll;
    ///
    L0=dif_l;
    L1=L0+LL;
    L2=L1+LL;
    L3=L2+LL;
    L4=L3+LL;
    L5=L4+LL;
    ///
    ///
    int nr_caractere=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {

            getmouseclick(WM_LBUTTONDOWN,x1,y1);

            ///numerele
            int var=100,ok3=0,ok2=0,ok1=0;
            settextstyle(8,0,1);
            ///

               // setcurrentwindow(window1);
             if(x1>Width-1.5*ll && x1<Width-ll/5 && y1>LL/5 && y1 <LL  )
    {
        int window2 = initwindow(600,600,"Indicatii de folosire");
        readimagefile("fundal2.jpg",0,0,600,600);
            setcurrentwindow(window2);
            if (getch())
            {
                closegraph(window2);
                setcurrentwindow(window1);
            }
    }
            ///
            if(x1>l0 && x1<l1 && y1>L0 &&y1<L1)
                {strcat(expresie,"1");
                 outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }

            if(x1>l0 && x1<l1 && y1>L1 &&y1<L2)
                {strcat(expresie,"2");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
            if(x1>l0 && x1<l1 && y1>L2 &&y1<L3)
                {strcat(expresie,"3");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
            if(x1>l0 && x1<l1 && y1>L3 &&y1<L4)
                {strcat(expresie,"4");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;}
            if(x1>l0 && x1<l1 && y1>L4 &&y1<L5)
                {strcat(expresie,"5");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;}
            if(x1>l1 && x1<l2 && y1>L0 &&y1<L1)
                {strcat(expresie,"6");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;}
            if(x1>l1 && x1<l2 && y1>L1 &&y1<L2)
                {strcat(expresie,"7");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;}
            if(x1>l1 && x1<l2 && y1>L2 &&y1<L3)
                {strcat(expresie,"8");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;}
            if(x1>l1 && x1<l2 && y1>L3 &&y1<L4)
                {strcat(expresie,"9");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
            if(x1>l1 && x1<l2 && y1>L4 &&y1<L5)
                {strcat(expresie,"0");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
            ////////////////////////////////////////////
            if (x1>l2 && x1<l3 && y1>L0 && y1<L1)
                {
                 strcat(expresie,"sin");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=30;
                 ok1=3;
                }

            if (x1>l3 && x1<l4 && y1>L0 && y1<L1)
                {strcat(expresie,"+");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
            if (x1>l3 && x1<l4 && y1>L1 && y1<L2)
                {strcat(expresie,"-");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;}
            if (x1>l3 && x1<l4 && y1>L2 && y1<L3)
                {strcat(expresie,"*");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                 }
            if (x1>l3 && x1<l4 && y1>L3 && y1<L4)
                {strcat(expresie,"/");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
            if (x1>l3 && x1<l4 && y1>L4 && y1<L5)
                {strcat(expresie,"^");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
            ///////////////////////////////////////////
            if (x1>l4 && x1<l5-(l5-l4)/2 && y1>L3 && y1<L4)
                {strcat(expresie,"(");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
            if (x1>l4+(l5-l4)/2 && x1<l5 && y1>L3 && y1<L4)
                {strcat(expresie,")");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
            if (x1>l4 && x1<l5 && y1>L0 && y1<L1)
            {

            {
                if(expresie[strlen(expresie)-1]=='n' || expresie[strlen(expresie)-1]=='s' ||
                    (expresie[strlen(expresie)-3]=='c' && expresie[strlen(expresie)-2]=='t'))
                    for(int i=1; i<=3; i++)
                    {

                        strcpy(strlen(expresie)+expresie-1, strlen(expresie)+expresie);
                        ///
                        outtextxy(var,Height-dif_l+20,expresie);
                 var=var-ok1*10;
                 setfillstyle(SOLID_FILL,0);
                 floodfill(11*spatiu,Height-dif_l+20,2);
                 outtextxy(var,Height-dif_l+20,expresie);
                        ///

                    }
                else if(expresie[strlen(expresie)-2]=='t' && expresie[strlen(expresie)-3]!='c')
                    for(int i=1; i<=2; i++)
                    {

                        strcpy(strlen(expresie)+expresie-1, strlen(expresie)+expresie);
                ///
                        outtextxy(var,Height-dif_l+20,expresie);
                 var=var-ok1*10;
                 setfillstyle(SOLID_FILL,0);
                 floodfill(11*spatiu,Height-dif_l+20,2);
                 outtextxy(var,Height-dif_l+20,expresie);
                        ///

                    }
                else
                {

                    strcpy(strlen(expresie)+expresie-1,strlen(expresie)+expresie);
                    outtextxy(var,Height-dif_l+20,expresie);
                 var=var-ok1*10;
                 setfillstyle(SOLID_FILL,0);
                 floodfill(11*spatiu,Height-dif_l+20,2);
                 outtextxy(var,Height-dif_l+20,expresie);

                }
            }

            }
            if (x1>l4 && x1<l5 && y1>L1 && y1<L2)
                {
                 strcat(expresie,"x");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
                if(x1>l4 && x1<l5 && y1>L3-LL/2 && y1<L3 )
                {
                 strcat(expresie,"pi");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=20;
                 ok1=2;
                }
            if (x1>l4 && x1<l5 && y1>L2 && y1<L2+LL/2)
                {
                    strcat(expresie,"e");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=10;
                 ok1=1;
                }
            if (x1>l2 && x1<l3 && y1>L1 && y1<L2)
                {strcat(expresie,"cos");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=30;
                 ok1=3;}
            if (x1>l2 && x1<l3 && y1>L2 && y1<L3)
                {strcat(expresie,"tan");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=30;
                 ok1=3;
                }
            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            if (x1>l2 && x1<l3 && y1>L3 && y1<L4)
            {
                strcat(expresie,"ctg");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=30;
                 ok1=3;
            }


            if (x1>l2 && x1<l3 && y1>L4 && y1<L5)

                    {
                ok1=3;
                strcat(expresie,"log");
                outtextxy(var,Height-dif_l+20,expresie);
                 var+=30;
                setcolor(9);
                settextstyle(10,0,2);
                outtextxy(dif_L+5,Height-dif_l+15,"Apasati enter apoi ");
                outtextxy(dif_L+5,Height-dif_l+45,"introduceti baza dorita. ");

                if (getch())
                {
                    setfillstyle(SOLID_FILL,0);
                    floodfill(dif_L+15,Height-dif_l+25, 2);
                }
                }
                if(x1>l4 && x1<l5 && y1>L4 && y1 < L5)
                    {ok=1;
                    //settextstyle(8,0,1);
                    //outtextxy(10*spatiu,Height-dif_l+60,expresie_finala);
                    }
                setcolor(14);
                ///
            ///meniu ajutator

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //cout<<endl<<expresie<<endl;
            //cout<<x1<<" "<<y1<<endl;
        }
    }
    while(ok==0);
    /////////////////////////////
    /////////////////////////////
    expresia2[0]='(';
    strcat(expresia2,expresie);
    expresia2[strlen(expresia2)]=')';
    strcpy(expresie,expresia2);
    Vectorizeaza(expresie,vectorul);
    Arborizeaza(vectorul,arborele);
    Deriveaza(arborele,arborele_derivat);
    ///

    ///
    parcurgereInOrdine(arborele_derivat);

   settextstyle(8,0,1);
    outtextxy(100,Height-dif_l+60,expresie_finala);
    system("pause");
}


/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    meniu_grafica();

    return 0;
}
