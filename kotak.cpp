#include <iostream> 
#include <conio.h> 
#include <time.h>
#include <windows.h>

#define posisi_pekmen 2
#define posisi_duri 74

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pekmen;
int laju = 100;
int selesai = 0;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setcursor(bool visible, DWORD size){
    if (size == 0) {
        size = 20;
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, & lpCursor);
}


void skor() {
    system("cls"); 
    selesai = 0;
    gotoxy(3, 2); cout<<"Skor : ";
    for (int i=0;i<79;i++){
    	gotoxy(1+i, 1); cout<<"�";
    	gotoxy(1+i, 25); cout<<"�";
	} 
}

void gerakan(int lompat = 0) {
    static int kaki = 0;

    if (lompat == 0)
        pekmen = 0;
    else if (lompat == 2)
        pekmen--;
    else pekmen++;

    gotoxy(posisi_pekmen, 15 - pekmen);cout<<"                 ";
    gotoxy(posisi_pekmen, 16 - pekmen);cout<<"         ��������";
    gotoxy(posisi_pekmen, 17 - pekmen);cout<<"         ��������";
    gotoxy(posisi_pekmen, 18 - pekmen);cout<<"         ��������";
    gotoxy(posisi_pekmen, 19 - pekmen);cout<<" �      �������� ";
    gotoxy(posisi_pekmen, 20 - pekmen);cout<<" ���  ���������� ";
    gotoxy(posisi_pekmen, 21 - pekmen);cout<<" ������������  � ";
    gotoxy(posisi_pekmen, 22 - pekmen);cout<<"   ���������     ";
    gotoxy(posisi_pekmen, 23 - pekmen);

    if (lompat == 1 || lompat == 2) {
        cout<<"    ��� ��       ";
        gotoxy(2, 24 - pekmen);
        cout<<"    ��   ��      ";
    } 
	else if (kaki == 0) {
        cout<<"    ����  ���    ";
        gotoxy(2, 24 - pekmen);
        cout<<"      ��         ";
        kaki = !kaki;
    } 
	else if (kaki == 1) {
        cout<<"     ��� ��      ";
        gotoxy(2, 24 - pekmen);
        cout<<"          ��     ";
        kaki = !kaki;
    }
    
    gotoxy(2, 25 - pekmen);
    if (lompat == 0) {
        cout<<"�����������������";
    } else {
        cout<<"                ";
    } 
    Sleep(laju);
}

void duri() {
    static int tajam = 0;
	static int skor = 0;
    if (tajam == 56 && pekmen < 4) {
        skor = 0;
        laju = 40;
        gotoxy(36, 8);cout<<"Game Over";
        getch();
        selesai = 1; 
    }
    
    gotoxy(posisi_duri - tajam, 20);cout<<"        ";
    gotoxy(posisi_duri - tajam, 21);cout<<" 	   ";
    gotoxy(posisi_duri - tajam, 22);cout<<"   �    ";
    gotoxy(posisi_duri - tajam, 23);cout<<"  ���   ";
    gotoxy(posisi_duri - tajam, 24);cout<<" �����  ";
     
    tajam++;
    
    if (tajam == 73) {
        tajam = 0;
        skor++;
        gotoxy(11, 2);cout<<"     ";
        gotoxy(11, 2);cout<<skor;
        if (laju > 20)
            laju--;
    }
}

void mulai(){ 
	system("cls");
    char ch;
    int i;
	skor();
    while (true) {
        while (!kbhit()) {
            if( selesai==1 ){
            	return;
			}
			gerakan();
            duri();
        }
        ch = getch();
        if (ch == 32) {
        	i = 0;
            while( i < 12) {
                gerakan(1);
                duri();
                i++;
            }
            while(i > 0) {
                gerakan(2);
                duri();
                i--;
        	}
        }
		else if (ch == 'p'||ch=='P')
           getch();
		else if (ch == 27)
           break;
    }
}

int main() {

    setcursor(0, 0);
    
    do{
		system("cls");
		gotoxy(10,5); cout<<" ������������������������ "; 
		gotoxy(10,6); cout<<" �      LOMPAT DURI     � ";  
		gotoxy(10,7); cout<<" ������������������������ ";
		gotoxy(10,9); cout<<"1. Mulai Permainan";
		gotoxy(10,10); cout<<"2. keluar";	 
		char op = getche();
		
		if( op=='1') mulai();
		else if( op=='2') exit(0);
		
	}while(1);
    
	return 0;
}
