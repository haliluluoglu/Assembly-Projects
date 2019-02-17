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
		MOVZX ECX, n		//Döngüde kullanýlacak n sayýsýný CX'e ata.		
		SHR ECX, 1			//Ýlk döngü matris satýrý/sutunu sayýnýn yarýsý kadar dönmeli.O yüzden yarýya düþürme iþlemi. 
		XOR EBX, EBX		//For döngülerinde kullanýlacak i deðiþkenini sýfýrlama.
disdon: PUSH ECX			//Ýkinci for döngüsü için ilk for döngüsünün son döngü miktarýný koruma.
		MOVZX ECX, n		//Ýkinci for için son döngü miktarý oluþturma.
		SUB ECX, EBX		//Ýkinci for döngüsünün son döngü miktarýnýn satýr/sutun sayýsýndan çýkarýlmasý.
		SUB ECX, EBX		//Ýkinci for döngüsünün son döngü miktarýnýn satýr/sutun sayýsýndan çýkarýlmasý.
		DEC ECX				//Ýkinci for döngüsünün son döngü miktarýnýn 1 azaltýlmasý.
		MOV EDX, EBX		//Ýkinci forun j deðiþkenine ilk döngü deðiþkeni i'nin atanmasý.
icdon:	MOV EAX, EBX		//Çarpýmýn yapýlabilmesi için i deðiþkeninin AX registera alýnmasý.(Ýlk indisin bulunmasý iþlemi.)
		PUSH EDX			//Çarpmadan DX registerýnýn etkilenmemesi için Stack'e atýlmasý.
		PUSH ECX			//Çarpmadan CX registerý satýr/sutun degerini temsil edecek. Eski deðerinin korunmasý.
		MOVZX ECX, n		//Çarpmadan CX registerý satýr/sutun degerini temsil edecek.
		MUL ECX				//n*i
		POP ECX				//Eski deðerinin çekilmesi.
		POP EDX				//Eski deðerinin çekilmesi.
		ADD EAX, EDX		//(n*i) + j
		SHL EAX, 1			//Adresin word tipinde ilerleyebilmesi için 2 ile çarpýlmasý.
		MOV EDI, resim		//Resim dizisinin adresinin kullanýlmak üzere DI'ya alýnmasý.
		ADD EDI, EAX		//Bulunan yeni indis deðerinin baþlangýç adresine eklenmesi.

		MOVZX EAX, n		//Çarpmadan AX registerý satýr/sutun degerini temsil edecek.
		SUB EAX, EDX		//n-j
		DEC EAX				//n-j-1
		PUSH EDX			//Çarpmadan DX registerýnýn etkilenmemesi için Stack'e atýlmasý.
		PUSH ECX			//Çarpmadan CX registerý satýr/sutun degerini temsil edecek. Eski deðerinin korunmasý.
		MOVZX ECX, n		//Çarpmadan CX registerý satýr/sutun degerini temsil edecek.
		MUL ECX				//(n-j-1) * n
		POP ECX				//Eski deðerinin çekilmesi.
		POP EDX				//Eski deðerinin çekilmesi.
		ADD EAX, EBX		//(n-j-1) * n + i

		MOV ESI, resim		//Resim dizisinin adresinin kullanýlmak üzere SI'ya alýnmasý.	
		SHL EAX, 1			//Adresin word tipinde ilerleyebilmesi için 2 ile çarpýlmasý.
		ADD ESI, EAX		//Bulunan yeni indis deðerinin baþlangýç adresine eklenmesi.(Ýkinci indisin bulunmasý)

		JMP temp1			//JUMP yapma sýnýrlarý aþýldýðý için kodun içinde kurduðum atlatma sistemi.
temp2 : JMP disdon
temp3 : JMP icdon
temp1 :
			
		PUSH EBX				//Swap yapmada kullanýlacak BX'in eski deðerinin korunmasý.
		MOV AX, WORD PTR[EDI]	//Ýlk bulunan adresin AX deðiþkenine atanmasý.(korunmasý)
		MOV BX, WORD PTR[ESI]	//Ýkinci bulunan adresin BX deðiþkenine atanmasý.(korunmasý)
		MOV WORD PTR[EDI], BX	//Ýkinci adresin ilk adrese atýlmasý deðiþkenine atanmasý.
		MOV WORD PTR[ESI], AX	//Ýlk adresin ikinci adrese atýlmasý deðiþkenine atanmasý.
		POP EBX					//Swap yapmada kullanýlan BX'in eski deðerinin çekilmesi.

		MOVZX EAX, n			//Çarpmadan AX registerý satýr/sutun degerini temsil edecek.
		SUB EAX, EBX			//n - i
		DEC EAX					//n - i -1
		PUSH EDX				//Çarpmadan DX registerýnýn etkilenmemesi için Stack'e atýlmasý.	
		PUSH ECX				//Çarpmadan CX registerý satýr/sutun degerini temsil edecek. Eski deðerinin korunmasý
		MOVZX ECX, n			//Çarpmadan CX registerý satýr/sutun degerini temsil edecek.
		MUL ECX					//(n - i -1) * n 
		POP ECX					//Eski deðerinin çekilmesi.
		POP EDX					//Eski deðerinin çekilmesi.
		PUSH ECX						
		MOVZX ECX, n			//Sutun/satir deðerinin kullanýlmak üzere CX'e alýnmasý.
		SUB ECX, EDX			//n - j
		DEC ECX					//n - j - 1
		ADD EAX, ECX			//(n - i -1) * n + n - j - 1
		POP ECX					//Eski deðerinin çekilmesi.

		MOV EDI, resim			//Resim dizisinin adresinin kullanýlmak üzere DI'ya alýnmasý.
		SHL EAX, 1				//Adresin word tipinde ilerleyebilmesi için yeni bulunan indisin 2 ile çarpýlmasý.
		ADD EDI, EAX			//Bulunan yeni indis deðerinin baþlangýç adresine eklenmesi.(Üçüncü indisin bulunmasý)

		PUSH EBX				// Swap yapmada kullanýlacak BX'in eski deðerinin korunmasý.
		MOV AX, WORD PTR[EDI]	//Ýlk bulunan adresin AX deðiþkenine atanmasý.(korunmasý)
		MOV BX, WORD PTR[ESI]	//Ýkinci bulunan adresin BX deðiþkenine atanmasý.(korunmasý)
		MOV WORD PTR[EDI], BX	//Ýkinci adresin ilk adrese atýlmasý deðiþkenine atanmasý.
		MOV WORD PTR[ESI], AX	//Ýlk adresin ikinci adrese atýlmasý deðiþkenine atanmasý.
		POP EBX					//Swap yapmada kullanýlan BX'in eski deðerinin çekilmesi.
				
		MOV EAX, EDX			//Çarpmadan AX registerý i degerini temsil edecek.
		PUSH EDX				//Eski deðerinin korunmasý.
		PUSH ECX				//Eski deðerinin korunmasý.
		MOVZX ECX, n			//Çarpmadan CX registerý satýr/sutun degerini temsil edecek.
		MUL ECX					//j * n
		POP ECX					//Eski deðerinin çekilmesi.
		POP EDX					//Eski deðerinin çekilmesi.

		PUSH ECX				//Eski deðerinin korunmasý.
		MOVZX ECX, n			//Matris sutun/satýr sayýnýnýn kullanýlmak üzere CX'e alýnmasý.
		SUB ECX, EBX			//n - i
		DEC ECX					//n - i - 1
		ADD EAX, ECX			//(n * j) + (n - i - 1)
		POP ECX					//Eski deðerinin çekilmesi.

		MOV ESI, resim			// Resim dizisinin adresinin kullanýlmak üzere SI'ya alýnmasý.
		SHL EAX, 1				//Adresin word tipinde ilerleyebilmesi için yeni bulunan indisin 2 ile çarpýlmasý.
		ADD ESI, EAX			//Bulunan yeni indis deðerinin baþlangýç adresine eklenmesi.(Dördüncü indisin bulunmasý)

		PUSH EBX				// Swap yapmada kullanýlacak BX'in eski deðerinin korunmasý.
		MOV AX, WORD PTR[EDI]	//Ýlk bulunan adresin AX deðiþkenine atanmasý.(korunmasý)
		MOV BX, WORD PTR[ESI]	//Ýkinci bulunan adresin BX deðiþkenine atanmasý.(korunmasý)
		MOV WORD PTR[EDI], BX	//Ýkinci adresin ilk adrese atýlmasý deðiþkenine atanmasý.
		MOV WORD PTR[ESI], AX	//Ýlk adresin ikinci adrese atýlmasý deðiþkenine atanmasý.
		POP EBX					//Swap yapmada kullanýlan BX'in eski deðerinin çekilmesi.

		INC EDX					//Ýç döngü deðiþkeni olan i nin arttýrýlmasý.
		LOOP temp3				//Döngünü baþa dönmesi.
		POP ECX					//Dýþ döngünün dönme miktarý deðerinin çekilmesi.
		INC EBX					//Dýþ döngü deðiþkeni olan j nin arttýrýlmasý
		LOOP temp2				//Döngünü baþa dönmesi.
	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}

void solaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	__asm {
		MOVZX ECX, n		//Döngüde kullanýlacak n sayýsýný CX'e ata.
		SHR ECX, 1			//Ýlk döngü matris satýrý/sutunu sayýnýn yarýsý kadar dönmeli.O yüzden yarýya düþürme iþlemi. 
		XOR EBX,EBX			//For döngülerinde kullanýlacak i deðiþkenini sýfýrlama.
disdon: PUSH ECX			//Ýkinci for döngüsü için ilk for döngüsünün son döngü miktarýný koruma.
		MOVZX ECX, n		//Ýkinci for için son döngü miktarý oluþturma.
		SUB ECX, EBX		//Ýkinci for döngüsünün son döngü miktarýnýn satýr/sutun sayýsýndan çýkarýlmasý.
		SUB ECX, EBX		//Ýkinci for döngüsünün son döngü miktarýnýn satýr/sutun sayýsýndan çýkarýlmasý.
		DEC ECX				//Ýkinci for döngüsünün son döngü miktarýnýn 1 azaltýlmasý.
		MOV EDX, EBX		//Ýkinci forun i deðiþkenine ilk döngü deðiþkeni i'nin atanmasý.
icdon:	MOV EAX, EBX		//Çarpýmýn yapýlabilmesi için i deðiþkeninin AX registera alýnmasý.(Ýlk indisin bulunmasý iþlemi.)
		PUSH EDX			//Çarpmadan DX registerýnýn etkilenmemesi için Stack'e atýlmasý.
		PUSH ECX			//Çarpmadan CX registerý satýr/sutun degerini temsil edecek. Eski deðerinin korunmasý.
		MOVZX ECX, n		//Çarpmadan CX registerý satýr/sutun degerini temsil edecek.
		MUL ECX				//n*i
		POP ECX				//Eski deðerinin çekilmesi.
		POP EDX				//Eski deðerinin çekilmesi.
		ADD EAX, EDX		//(n*i) + j
		SHL EAX, 1			//Adresin word tipinde ilerleyebilmesi için 2 ile çarpýlmasý.
		MOV EDI, resim		//Resim dizisinin adresinin kullanýlmak üzere DI'ya alýnmasý.
		ADD EDI, EAX		//Bulunan yeni indis deðerinin baþlangýç adresine eklenmesi.

		MOV EAX, EDX		//Çarpmadan AX registerý j degerini temsil edecek.
		PUSH EDX			//Çarpmadan DX registerýnýn etkilenmemesi için Stack'e atýlmasý.
		PUSH ECX			//Çarpmadan CX registerý satýr/sutun degerini temsil edecek. Eski deðerinin korunmasý.
		MOVZX ECX, n		//Çarpmadan CX registerý satýr/sutun degerini temsil edecek.
		MUL ECX				//(n * j)
		POP ECX				//Eski deðerinin çekilmesi.
		POP EDX				//Eski deðerinin çekilmesi.	

		PUSH ECX			//Çarpmadan CX registerý satýr/sutun degerini temsil edecek. Eski deðerinin korunmasý.
		MOVZX ECX, n		//Çarpmadan CX registerý satýr/sutun degerini temsil edecek.
		SUB ECX, EBX		//(n - i)
		DEC ECX				//(n - i - 1)
		ADD EAX, ECX		//(n - i - 1) + (n * j)
		POP ECX				//Eski deðerinin çekilmesi.

		MOV ESI, resim		//Resim dizisinin adresinin kullanýlmak üzere SI'ya alýnmasý.	
		SHL EAX, 1			//Adresin word tipinde ilerleyebilmesi için 2 ile çarpýlmasý.
		ADD ESI, EAX		//Bulunan yeni indis deðerinin baþlangýç adresine eklenmesi.(Ýkinci indisin bulunmasý)
		
		PUSH EBX				//Swap yapmada kullanýlacak BX'in eski deðerinin korunmasý.
		MOV AX, WORD PTR[EDI]	//Ýlk bulunan adresin AX deðiþkenine atanmasý.(korunmasý)
		MOV BX, WORD PTR[ESI]	//Ýkinci bulunan adresin BX deðiþkenine atanmasý.(korunmasý)
		MOV WORD PTR[EDI], BX	//Ýkinci adresin ilk adrese atýlmasý deðiþkenine atanmasý.
		MOV WORD PTR[ESI], AX	//Ýlk adresin ikinci adrese atýlmasý deðiþkenine atanmasý.
		POP EBX					//Swap yapmada kullanýlan BX'in eski deðerinin çekilmesi.


		MOVZX EAX,n				//Çarpmadan AX registerý satýr/sutun degerini temsil edecek.
		SUB EAX,EBX				//(n - i)
		DEC EAX					//(n - i - 1)
		PUSH EDX				//Çarpmadan DX registerýnýn etkilenmemesi için Stack'e atýlmasý.	
		PUSH ECX				// Çarpmadan CX registerý satýr / sutun degerini temsil edecek.Eski deðerinin korunmasý
		MOVZX ECX, n			//Çarpmadan CX registerý satýr/sutun degerini temsil edecek.
		MUL ECX					//(n - i - 1) * n
		POP ECX					//Eski deðerinin çekilmesi.
		POP EDX					//Eski deðerinin çekilmesi.
		PUSH ECX				//Eski deðerinin korunmasý.
		MOVZX ECX,n				//Sutun/satir deðerinin kullanýlmak üzere CX'e alýnmasý.
		SUB ECX,EDX				//(n - j)
		DEC ECX					//(n - j - 1)
		ADD EAX,ECX				//(n - j - 1) + (n - i - 1) * n
		POP ECX					//Eski deðerinin çekilmesi.
		
		SHL EAX, 1				// Adresin word tipinde ilerleyebilmesi için 2 ile çarpýlmasý.
		MOV EDI, resim			//Resim dizisinin adresinin kullanýlmak üzere DI'ya alýnmasý.
		ADD EDI,EAX				//Bulunan yeni indis deðerinin baþlangýç adresine eklenmesi.(Üçüncü indisin bulunmasý)

		JMP temp1				//JUMP yapma sýnýrlarý aþýldýðý için kodun içinde kurduðum atlatma sistemi.
temp2:		JMP disdon
temp3:		JMP icdon
temp1:
		PUSH EBX				//Swap yapmada kullanýlacak BX'in eski deðerinin korunmasý.
		MOV AX, WORD PTR[EDI]	//Ýlk bulunan adresin AX deðiþkenine atanmasý.(korunmasý)
		MOV BX,WORD PTR[ESI]	//Ýkinci bulunan adresin BX deðiþkenine atanmasý.(korunmasý)
		MOV WORD PTR[EDI], BX	//Ýkinci adresin ilk adrese atýlmasý deðiþkenine atanmasý.
		MOV WORD PTR[ESI], AX	//Ýlk adresin ikinci adrese atýlmasý deðiþkenine atanmasý.
		POP EBX					//Swap yapmada kullanýlan BX'in eski deðerinin çekilmesi.

		MOV EAX,EDX				//Çarpmadan AX registerý j degerini temsil edecek.
		PUSH EDX				//Eski deðerinin korunmasý.
		PUSH ECX				//Eski deðerinin korunmasý.
		MOVZX ECX, n			//Çarpmadan CX registerý satýr/sutun degerini temsil edecek.
		MUL ECX					//(n * j)
		POP ECX					//Eski deðerinin çekilmesi.
		POP EDX					//Eski deðerinin çekilmesi.
				
		PUSH ECX				//Eski deðerinin korunmasý.
		MOVZX ECX,n				//Sutun/satir deðerinin kullanýlmak üzere CX'e alýnmasý.
		SUB ECX,EBX				//(n - i)
		DEC ECX					//(n - i - 1)
		ADD EAX,ECX				//(n - i - 1) + (n * j)
		POP ECX					//Eski deðerinin çekilmesi.


		SHL EAX, 1				//Adresin word tipinde ilerleyebilmesi için yeni bulunan indisin 2 ile çarpýlmasý.
		MOV ESI, resim			//Resim dizisinin adresinin kullanýlmak üzere SI'ya alýnmasý.
		ADD ESI,EAX				//Bulunan yeni indis deðerinin baþlangýç adresine eklenmesi.(Dördüncü indisin bulunmasý)

		MOVZX EAX, n			//Çarpmadan AX registerý n degerini temsil edecek.
		SUB EAX, EDX			//(n - j)
		DEC EAX					//(n - j - 1)
		PUSH EDX				//Eski deðerinin korunmasý.
		PUSH ECX				//Eski deðerinin korunmasý.
		MOVZX ECX, n			//Çarpmadan CX registerý satýr/sutun degerini temsil edecek.
		MUL ECX					//(n - j - 1) * n
		POP ECX					//Eski deðerinin çekilmesi.
		POP EDX					//Eski deðerinin çekilmesi.

		ADD EAX, EBX			//(n - j - 1) * n + i
		SHL EAX, 1				//Adresin word tipinde ilerleyebilmesi için yeni bulunan indisin 2 ile çarpýlmasý.
		MOV ESI, resim			// Resim dizisinin adresinin kullanýlmak üzere SI'ya alýnmasý.
		ADD ESI, EAX			//Bulunan yeni indis deðerinin baþlangýç adresine eklenmesi.(Dördüncü indisin bulunmasý)


		PUSH EBX				// Swap yapmada kullanýlacak BX'in eski deðerinin korunmasý.
		MOV AX, WORD PTR[EDI]	//Ýlk bulunan adresin AX deðiþkenine atanmasý.(korunmasý)
		MOV BX, WORD PTR[ESI]	//Ýkinci bulunan adresin BX deðiþkenine atanmasý.(korunmasý)
		MOV WORD PTR[EDI], BX	//Ýkinci adresin ilk adrese atýlmasý deðiþkenine atanmasý.
		MOV WORD PTR[ESI], AX	//Ýlk adresin ikinci adrese atýlmasý deðiþkenine atanmasý.
		POP EBX					//Swap yapmada kullanýlan BX'in eski deðerinin çekilmesi.

		INC EDX					//Ýç döngü deðiþkeni olan j nin arttýrýlmasý.
		LOOP temp3				//Döngünü baþa dönmesi.
		POP ECX					//Dýþ döngünün dönme miktarý deðerinin çekilmesi.
		INC EBX					//Dýþ döngü deðiþkeni olan j nin arttýrýlmasý
		LOOP temp2				//Döngünü baþa dönmesi.

	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}