Elemente de grafica pe calculator - Tema 2
	Nume tema : World Builder
	Nume si prenume : Cazacu Roxana Andreea
	Grupa : 334CC

Cerinta:
	Utilizand framework-ul din laboratorul 3, am avut de implementat o mini-lume, si anume posibilitatea de a adauga pe o grila, case, piete, drumuri,
teren si apa.

Platforma folosita :
	IDE : Microsoft Visual Studio 2012
	Sistem de operare : Windows 8.1
	
Implementare :
	Am lucrat pe framework-ul oferit de laborator, mai exact pe scheletul de la al treilea laborator. Toata implementarea este facuta in main.cpp,
modificand insa perspectiva in DrawingWindow.cpp. Nu am folosit nicio functie, am scris in onKey si init.
	In init am desenat grila, iar in onKey am implementat tastele si anume:
		-pentru scroll grila am folosit tastele : 2(jos), 8(sus), 4(stanga), 6(dreapta)
		-pentru miscat pozitia curenta am folosit sagetile
		-pentru comutare intre modurile de editare : t(teren), a(apa), 1(drum)
		-pentru a sterge un obiect : b(back)
		-pentru a construi casa : c , iar pentru piata : p 
	
Continutul arhivei :
	-fisierele cu framework-ul din laboratorul 3
	-Screenshot.png //o forma finala a mini-lumii
	-README

Functionalitati :
	Functionalitati standard:
		-editare mod comutare intre teren, apa si drum
		-adaugare case si piete
		-vizualizarea intregii grile folosind scroll-ul
		-posibilitatea de a reveni la pozitia anterioara a grilei
	