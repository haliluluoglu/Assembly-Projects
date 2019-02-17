#pragma warning(disable: 4996)
#include <windows.h>
#include <stdio.h>

#include <string.h>
#include <math.h>
#include <iostream>
#include "image_processing.cpp"
//#define _CRT_SECURE_NO_WARNINGS

using namespace std;

void sagaDondur(short n, int resim);
void solaDondur(short n, int resim);

int main(void) {
	int M, N, Q, i, j, k;
	bool type;
	int efile, islem;
	char resimadi[100], sonek[10];
	printf("Halil ibrahim Uluoglu\n");
	printf("16011093\n");
	do {
		printf("Islem yapilacak resmin yolunu (path) giriniz:\n-> ");
		scanf("%s", &resimadi);
		system("CLS");
		efile = readImageHeader(resimadi, N, M, Q, type);
	} while (efile > 1);
	printf("%s\n", resimadi);
	int** resim = resimOku(resimadi);

	short *resimdizi;
	resimdizi = (short*) malloc(N*M * sizeof(short));

	for (i = 0; i < N; i++) 
		for (j = 0; j < M; j++) 
			resimdizi[i*N + j] = (short) resim[i][j];

	int resimadres = (int) resimdizi;

	do {
		system("CLS");
		printf("\t     ISLEMLER\n");
		printf("------------------------------------\n");
		printf("1)  Resmi saga dondur\n");
		printf("2)  Resmi sola dondur\n");
		printf("0)  Cikis\n\n");
		printf("\"%s\" yolundaki resim icin yapilacak islemi seciniz\n-> ", resimadi);
		scanf("%d", &islem);
	} while (islem > 2 || islem < 0);

	switch (islem) {
		case 0:
			exit(0);
		case 1:
			sagaDondur(N, resimadres);
			strcpy(sonek, "_sag.pgm");
			break;
		case 2:
			solaDondur(N , resimadres);
			strcpy(sonek, "_sol.pgm");
			break;
		default:
			strcpy(sonek, "_orj.pgm");
			break;
	}

	for (k = 0; k < N * M; k++) {
		j = k % N;
		i = k / N;
		resim[i][j] = (int)resimdizi[k];
	}
	
	string::size_type pos = string(resimadi).find_last_of(".");
	resimadi[pos] = '\0';
	strcat(resimadi, sonek);
	resimYaz(resimadi, resim, N, M, Q);
	printf("Halil ibrahim Uluoglu\n");
	printf("16011093\n");
	printf("\nIslem basariyla tamamlandi :)\n\"%s\" yolunda resim olusturuldu.\n\n", resimadi);
	system("PAUSE");
	return 0;
}

void sagaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	__asm {
		MOVZX ECX, n		//D�ng�de kullan�lacak n say�s�n� CX'e ata.		
		SHR ECX, 1			//�lk d�ng� matris sat�r�/sutunu say�n�n yar�s� kadar d�nmeli.O y�zden yar�ya d���rme i�lemi. 
		XOR EBX, EBX		//For d�ng�lerinde kullan�lacak i de�i�kenini s�f�rlama.
disdon: PUSH ECX			//�kinci for d�ng�s� i�in ilk for d�ng�s�n�n son d�ng� miktar�n� koruma.
		MOVZX ECX, n		//�kinci for i�in son d�ng� miktar� olu�turma.
		SUB ECX, EBX		//�kinci for d�ng�s�n�n son d�ng� miktar�n�n sat�r/sutun say�s�ndan ��kar�lmas�.
		SUB ECX, EBX		//�kinci for d�ng�s�n�n son d�ng� miktar�n�n sat�r/sutun say�s�ndan ��kar�lmas�.
		DEC ECX				//�kinci for d�ng�s�n�n son d�ng� miktar�n�n 1 azalt�lmas�.
		MOV EDX, EBX		//�kinci forun j de�i�kenine ilk d�ng� de�i�keni i'nin atanmas�.
icdon:	MOV EAX, EBX		//�arp�m�n yap�labilmesi i�in i de�i�keninin AX registera al�nmas�.(�lk indisin bulunmas� i�lemi.)
		PUSH EDX			//�arpmadan DX register�n�n etkilenmemesi i�in Stack'e at�lmas�.
		PUSH ECX			//�arpmadan CX register� sat�r/sutun degerini temsil edecek. Eski de�erinin korunmas�.
		MOVZX ECX, n		//�arpmadan CX register� sat�r/sutun degerini temsil edecek.
		MUL ECX				//n*i
		POP ECX				//Eski de�erinin �ekilmesi.
		POP EDX				//Eski de�erinin �ekilmesi.
		ADD EAX, EDX		//(n*i) + j
		SHL EAX, 1			//Adresin word tipinde ilerleyebilmesi i�in 2 ile �arp�lmas�.
		MOV EDI, resim		//Resim dizisinin adresinin kullan�lmak �zere DI'ya al�nmas�.
		ADD EDI, EAX		//Bulunan yeni indis de�erinin ba�lang�� adresine eklenmesi.

		MOVZX EAX, n		//�arpmadan AX register� sat�r/sutun degerini temsil edecek.
		SUB EAX, EDX		//n-j
		DEC EAX				//n-j-1
		PUSH EDX			//�arpmadan DX register�n�n etkilenmemesi i�in Stack'e at�lmas�.
		PUSH ECX			//�arpmadan CX register� sat�r/sutun degerini temsil edecek. Eski de�erinin korunmas�.
		MOVZX ECX, n		//�arpmadan CX register� sat�r/sutun degerini temsil edecek.
		MUL ECX				//(n-j-1) * n
		POP ECX				//Eski de�erinin �ekilmesi.
		POP EDX				//Eski de�erinin �ekilmesi.
		ADD EAX, EBX		//(n-j-1) * n + i

		MOV ESI, resim		//Resim dizisinin adresinin kullan�lmak �zere SI'ya al�nmas�.	
		SHL EAX, 1			//Adresin word tipinde ilerleyebilmesi i�in 2 ile �arp�lmas�.
		ADD ESI, EAX		//Bulunan yeni indis de�erinin ba�lang�� adresine eklenmesi.(�kinci indisin bulunmas�)

		JMP temp1			//JUMP yapma s�n�rlar� a��ld��� i�in kodun i�inde kurdu�um atlatma sistemi.
temp2 : JMP disdon
temp3 : JMP icdon
temp1 :
			
		PUSH EBX				//Swap yapmada kullan�lacak BX'in eski de�erinin korunmas�.
		MOV AX, WORD PTR[EDI]	//�lk bulunan adresin AX de�i�kenine atanmas�.(korunmas�)
		MOV BX, WORD PTR[ESI]	//�kinci bulunan adresin BX de�i�kenine atanmas�.(korunmas�)
		MOV WORD PTR[EDI], BX	//�kinci adresin ilk adrese at�lmas� de�i�kenine atanmas�.
		MOV WORD PTR[ESI], AX	//�lk adresin ikinci adrese at�lmas� de�i�kenine atanmas�.
		POP EBX					//Swap yapmada kullan�lan BX'in eski de�erinin �ekilmesi.

		MOVZX EAX, n			//�arpmadan AX register� sat�r/sutun degerini temsil edecek.
		SUB EAX, EBX			//n - i
		DEC EAX					//n - i -1
		PUSH EDX				//�arpmadan DX register�n�n etkilenmemesi i�in Stack'e at�lmas�.	
		PUSH ECX				//�arpmadan CX register� sat�r/sutun degerini temsil edecek. Eski de�erinin korunmas�
		MOVZX ECX, n			//�arpmadan CX register� sat�r/sutun degerini temsil edecek.
		MUL ECX					//(n - i -1) * n 
		POP ECX					//Eski de�erinin �ekilmesi.
		POP EDX					//Eski de�erinin �ekilmesi.
		PUSH ECX						
		MOVZX ECX, n			//Sutun/satir de�erinin kullan�lmak �zere CX'e al�nmas�.
		SUB ECX, EDX			//n - j
		DEC ECX					//n - j - 1
		ADD EAX, ECX			//(n - i -1) * n + n - j - 1
		POP ECX					//Eski de�erinin �ekilmesi.

		MOV EDI, resim			//Resim dizisinin adresinin kullan�lmak �zere DI'ya al�nmas�.
		SHL EAX, 1				//Adresin word tipinde ilerleyebilmesi i�in yeni bulunan indisin 2 ile �arp�lmas�.
		ADD EDI, EAX			//Bulunan yeni indis de�erinin ba�lang�� adresine eklenmesi.(���nc� indisin bulunmas�)

		PUSH EBX				// Swap yapmada kullan�lacak BX'in eski de�erinin korunmas�.
		MOV AX, WORD PTR[EDI]	//�lk bulunan adresin AX de�i�kenine atanmas�.(korunmas�)
		MOV BX, WORD PTR[ESI]	//�kinci bulunan adresin BX de�i�kenine atanmas�.(korunmas�)
		MOV WORD PTR[EDI], BX	//�kinci adresin ilk adrese at�lmas� de�i�kenine atanmas�.
		MOV WORD PTR[ESI], AX	//�lk adresin ikinci adrese at�lmas� de�i�kenine atanmas�.
		POP EBX					//Swap yapmada kullan�lan BX'in eski de�erinin �ekilmesi.
				
		MOV EAX, EDX			//�arpmadan AX register� i degerini temsil edecek.
		PUSH EDX				//Eski de�erinin korunmas�.
		PUSH ECX				//Eski de�erinin korunmas�.
		MOVZX ECX, n			//�arpmadan CX register� sat�r/sutun degerini temsil edecek.
		MUL ECX					//j * n
		POP ECX					//Eski de�erinin �ekilmesi.
		POP EDX					//Eski de�erinin �ekilmesi.

		PUSH ECX				//Eski de�erinin korunmas�.
		MOVZX ECX, n			//Matris sutun/sat�r say�n�n�n kullan�lmak �zere CX'e al�nmas�.
		SUB ECX, EBX			//n - i
		DEC ECX					//n - i - 1
		ADD EAX, ECX			//(n * j) + (n - i - 1)
		POP ECX					//Eski de�erinin �ekilmesi.

		MOV ESI, resim			// Resim dizisinin adresinin kullan�lmak �zere SI'ya al�nmas�.
		SHL EAX, 1				//Adresin word tipinde ilerleyebilmesi i�in yeni bulunan indisin 2 ile �arp�lmas�.
		ADD ESI, EAX			//Bulunan yeni indis de�erinin ba�lang�� adresine eklenmesi.(D�rd�nc� indisin bulunmas�)

		PUSH EBX				// Swap yapmada kullan�lacak BX'in eski de�erinin korunmas�.
		MOV AX, WORD PTR[EDI]	//�lk bulunan adresin AX de�i�kenine atanmas�.(korunmas�)
		MOV BX, WORD PTR[ESI]	//�kinci bulunan adresin BX de�i�kenine atanmas�.(korunmas�)
		MOV WORD PTR[EDI], BX	//�kinci adresin ilk adrese at�lmas� de�i�kenine atanmas�.
		MOV WORD PTR[ESI], AX	//�lk adresin ikinci adrese at�lmas� de�i�kenine atanmas�.
		POP EBX					//Swap yapmada kullan�lan BX'in eski de�erinin �ekilmesi.

		INC EDX					//�� d�ng� de�i�keni olan i nin artt�r�lmas�.
		LOOP temp3				//D�ng�n� ba�a d�nmesi.
		POP ECX					//D�� d�ng�n�n d�nme miktar� de�erinin �ekilmesi.
		INC EBX					//D�� d�ng� de�i�keni olan j nin artt�r�lmas�
		LOOP temp2				//D�ng�n� ba�a d�nmesi.
	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}

void solaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	__asm {
		MOVZX ECX, n		//D�ng�de kullan�lacak n say�s�n� CX'e ata.
		SHR ECX, 1			//�lk d�ng� matris sat�r�/sutunu say�n�n yar�s� kadar d�nmeli.O y�zden yar�ya d���rme i�lemi. 
		XOR EBX,EBX			//For d�ng�lerinde kullan�lacak i de�i�kenini s�f�rlama.
disdon: PUSH ECX			//�kinci for d�ng�s� i�in ilk for d�ng�s�n�n son d�ng� miktar�n� koruma.
		MOVZX ECX, n		//�kinci for i�in son d�ng� miktar� olu�turma.
		SUB ECX, EBX		//�kinci for d�ng�s�n�n son d�ng� miktar�n�n sat�r/sutun say�s�ndan ��kar�lmas�.
		SUB ECX, EBX		//�kinci for d�ng�s�n�n son d�ng� miktar�n�n sat�r/sutun say�s�ndan ��kar�lmas�.
		DEC ECX				//�kinci for d�ng�s�n�n son d�ng� miktar�n�n 1 azalt�lmas�.
		MOV EDX, EBX		//�kinci forun i de�i�kenine ilk d�ng� de�i�keni i'nin atanmas�.
icdon:	MOV EAX, EBX		//�arp�m�n yap�labilmesi i�in i de�i�keninin AX registera al�nmas�.(�lk indisin bulunmas� i�lemi.)
		PUSH EDX			//�arpmadan DX register�n�n etkilenmemesi i�in Stack'e at�lmas�.
		PUSH ECX			//�arpmadan CX register� sat�r/sutun degerini temsil edecek. Eski de�erinin korunmas�.
		MOVZX ECX, n		//�arpmadan CX register� sat�r/sutun degerini temsil edecek.
		MUL ECX				//n*i
		POP ECX				//Eski de�erinin �ekilmesi.
		POP EDX				//Eski de�erinin �ekilmesi.
		ADD EAX, EDX		//(n*i) + j
		SHL EAX, 1			//Adresin word tipinde ilerleyebilmesi i�in 2 ile �arp�lmas�.
		MOV EDI, resim		//Resim dizisinin adresinin kullan�lmak �zere DI'ya al�nmas�.
		ADD EDI, EAX		//Bulunan yeni indis de�erinin ba�lang�� adresine eklenmesi.

		MOV EAX, EDX		//�arpmadan AX register� j degerini temsil edecek.
		PUSH EDX			//�arpmadan DX register�n�n etkilenmemesi i�in Stack'e at�lmas�.
		PUSH ECX			//�arpmadan CX register� sat�r/sutun degerini temsil edecek. Eski de�erinin korunmas�.
		MOVZX ECX, n		//�arpmadan CX register� sat�r/sutun degerini temsil edecek.
		MUL ECX				//(n * j)
		POP ECX				//Eski de�erinin �ekilmesi.
		POP EDX				//Eski de�erinin �ekilmesi.	

		PUSH ECX			//�arpmadan CX register� sat�r/sutun degerini temsil edecek. Eski de�erinin korunmas�.
		MOVZX ECX, n		//�arpmadan CX register� sat�r/sutun degerini temsil edecek.
		SUB ECX, EBX		//(n - i)
		DEC ECX				//(n - i - 1)
		ADD EAX, ECX		//(n - i - 1) + (n * j)
		POP ECX				//Eski de�erinin �ekilmesi.

		MOV ESI, resim		//Resim dizisinin adresinin kullan�lmak �zere SI'ya al�nmas�.	
		SHL EAX, 1			//Adresin word tipinde ilerleyebilmesi i�in 2 ile �arp�lmas�.
		ADD ESI, EAX		//Bulunan yeni indis de�erinin ba�lang�� adresine eklenmesi.(�kinci indisin bulunmas�)
		
		PUSH EBX				//Swap yapmada kullan�lacak BX'in eski de�erinin korunmas�.
		MOV AX, WORD PTR[EDI]	//�lk bulunan adresin AX de�i�kenine atanmas�.(korunmas�)
		MOV BX, WORD PTR[ESI]	//�kinci bulunan adresin BX de�i�kenine atanmas�.(korunmas�)
		MOV WORD PTR[EDI], BX	//�kinci adresin ilk adrese at�lmas� de�i�kenine atanmas�.
		MOV WORD PTR[ESI], AX	//�lk adresin ikinci adrese at�lmas� de�i�kenine atanmas�.
		POP EBX					//Swap yapmada kullan�lan BX'in eski de�erinin �ekilmesi.


		MOVZX EAX,n				//�arpmadan AX register� sat�r/sutun degerini temsil edecek.
		SUB EAX,EBX				//(n - i)
		DEC EAX					//(n - i - 1)
		PUSH EDX				//�arpmadan DX register�n�n etkilenmemesi i�in Stack'e at�lmas�.	
		PUSH ECX				// �arpmadan CX register� sat�r / sutun degerini temsil edecek.Eski de�erinin korunmas�
		MOVZX ECX, n			//�arpmadan CX register� sat�r/sutun degerini temsil edecek.
		MUL ECX					//(n - i - 1) * n
		POP ECX					//Eski de�erinin �ekilmesi.
		POP EDX					//Eski de�erinin �ekilmesi.
		PUSH ECX				//Eski de�erinin korunmas�.
		MOVZX ECX,n				//Sutun/satir de�erinin kullan�lmak �zere CX'e al�nmas�.
		SUB ECX,EDX				//(n - j)
		DEC ECX					//(n - j - 1)
		ADD EAX,ECX				//(n - j - 1) + (n - i - 1) * n
		POP ECX					//Eski de�erinin �ekilmesi.
		
		SHL EAX, 1				// Adresin word tipinde ilerleyebilmesi i�in 2 ile �arp�lmas�.
		MOV EDI, resim			//Resim dizisinin adresinin kullan�lmak �zere DI'ya al�nmas�.
		ADD EDI,EAX				//Bulunan yeni indis de�erinin ba�lang�� adresine eklenmesi.(���nc� indisin bulunmas�)

		JMP temp1				//JUMP yapma s�n�rlar� a��ld��� i�in kodun i�inde kurdu�um atlatma sistemi.
temp2:		JMP disdon
temp3:		JMP icdon
temp1:
		PUSH EBX				//Swap yapmada kullan�lacak BX'in eski de�erinin korunmas�.
		MOV AX, WORD PTR[EDI]	//�lk bulunan adresin AX de�i�kenine atanmas�.(korunmas�)
		MOV BX,WORD PTR[ESI]	//�kinci bulunan adresin BX de�i�kenine atanmas�.(korunmas�)
		MOV WORD PTR[EDI], BX	//�kinci adresin ilk adrese at�lmas� de�i�kenine atanmas�.
		MOV WORD PTR[ESI], AX	//�lk adresin ikinci adrese at�lmas� de�i�kenine atanmas�.
		POP EBX					//Swap yapmada kullan�lan BX'in eski de�erinin �ekilmesi.

		MOV EAX,EDX				//�arpmadan AX register� j degerini temsil edecek.
		PUSH EDX				//Eski de�erinin korunmas�.
		PUSH ECX				//Eski de�erinin korunmas�.
		MOVZX ECX, n			//�arpmadan CX register� sat�r/sutun degerini temsil edecek.
		MUL ECX					//(n * j)
		POP ECX					//Eski de�erinin �ekilmesi.
		POP EDX					//Eski de�erinin �ekilmesi.
				
		PUSH ECX				//Eski de�erinin korunmas�.
		MOVZX ECX,n				//Sutun/satir de�erinin kullan�lmak �zere CX'e al�nmas�.
		SUB ECX,EBX				//(n - i)
		DEC ECX					//(n - i - 1)
		ADD EAX,ECX				//(n - i - 1) + (n * j)
		POP ECX					//Eski de�erinin �ekilmesi.


		SHL EAX, 1				//Adresin word tipinde ilerleyebilmesi i�in yeni bulunan indisin 2 ile �arp�lmas�.
		MOV ESI, resim			//Resim dizisinin adresinin kullan�lmak �zere SI'ya al�nmas�.
		ADD ESI,EAX				//Bulunan yeni indis de�erinin ba�lang�� adresine eklenmesi.(D�rd�nc� indisin bulunmas�)

		MOVZX EAX, n			//�arpmadan AX register� n degerini temsil edecek.
		SUB EAX, EDX			//(n - j)
		DEC EAX					//(n - j - 1)
		PUSH EDX				//Eski de�erinin korunmas�.
		PUSH ECX				//Eski de�erinin korunmas�.
		MOVZX ECX, n			//�arpmadan CX register� sat�r/sutun degerini temsil edecek.
		MUL ECX					//(n - j - 1) * n
		POP ECX					//Eski de�erinin �ekilmesi.
		POP EDX					//Eski de�erinin �ekilmesi.

		ADD EAX, EBX			//(n - j - 1) * n + i
		SHL EAX, 1				//Adresin word tipinde ilerleyebilmesi i�in yeni bulunan indisin 2 ile �arp�lmas�.
		MOV ESI, resim			// Resim dizisinin adresinin kullan�lmak �zere SI'ya al�nmas�.
		ADD ESI, EAX			//Bulunan yeni indis de�erinin ba�lang�� adresine eklenmesi.(D�rd�nc� indisin bulunmas�)


		PUSH EBX				// Swap yapmada kullan�lacak BX'in eski de�erinin korunmas�.
		MOV AX, WORD PTR[EDI]	//�lk bulunan adresin AX de�i�kenine atanmas�.(korunmas�)
		MOV BX, WORD PTR[ESI]	//�kinci bulunan adresin BX de�i�kenine atanmas�.(korunmas�)
		MOV WORD PTR[EDI], BX	//�kinci adresin ilk adrese at�lmas� de�i�kenine atanmas�.
		MOV WORD PTR[ESI], AX	//�lk adresin ikinci adrese at�lmas� de�i�kenine atanmas�.
		POP EBX					//Swap yapmada kullan�lan BX'in eski de�erinin �ekilmesi.

		INC EDX					//�� d�ng� de�i�keni olan j nin artt�r�lmas�.
		LOOP temp3				//D�ng�n� ba�a d�nmesi.
		POP ECX					//D�� d�ng�n�n d�nme miktar� de�erinin �ekilmesi.
		INC EBX					//D�� d�ng� de�i�keni olan j nin artt�r�lmas�
		LOOP temp2				//D�ng�n� ba�a d�nmesi.

	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}