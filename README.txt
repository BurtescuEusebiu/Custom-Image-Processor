#README FILE
Programul editeaza imagini tranfosmate intr-o matrice tridimensionala formata din valorile culorilor in funcite de Rosu Verde si Albastru pentru fiecare pixel.
Cuprinde diferite functii de editare : crop,flip,rotate,extend,copy paste si apply filter.
Programul este operat prin intermediul introducerii anumitor comenzi.
Lista de comenzi, ce paramteri necesita si ce schimba:
e 	- 	Exit - închide programul
l 	N M path 	Load - alocă și încarcă imaginea de dimensiune NxM aflată la calea path
s 	index path 	Save - salvează imaginea de pe indexul index la calea specificată prin path
ah 	index 	Apply Horizontal Flip - aplică operația de flip pe orizontală imaginii de la indexul index
ar 	index 	Apply Rotate - aplică operația de rotație la stânga imaginii de la indexul index
ac 	index x y w h 	Apply Crop - aplică operația de crop cu parametrii dați imaginii de la indexul index
ae 	index rows cols R G B 	Apply Extend - aplică operația de extend cu parametrii dați imaginii de la indexul index
ap 	index_dst index_src x y 	Apply Paste - aplică operația de paste cu parametrii dați imaginii de la indexul index_dst
cf 	size [list of values] 	Create filter - alocă și crează un filtru de dimensiune size cu valorile date de lista de valori (exemplu: dacă se creează un filtru de dimensiune 3, atunci după size vor urma 9 valori
af 	index_img index_filter 	Apply filter - aplică filtrul de pe indexul index_filter pe imaginea de pe indexul index_img
df 	index_filter 	Delete filter - șterge și dezalocă filtrul de pe indexul index_filter
di 	index_img 	Delete image - șterge și dezalocă imaginea de pe indexul index_img

Programul nu are memory leaks si opereaza perfect atat timp cat sunt respectate urmatoarele reguli:

    path-urile nu vor avea lungime mai mare de 100 de caractere (puteți folosi o variabilă char path[100])
    path-urile nu vor conține spații (pot fi citite cu scanf(”%s”, path))
    fișierul din care se încarcă o imagine există și este valid
    comenzile date sunt mereu valide (nu se va da ca input o comandă inexistentă)
    parametrii comenzilor sunt mereu valizi (e.g. nu se va cere aplicarea unei procesări pe un index care nu există, sau paste la niște coordonate care încep în afara imaginii destinație etc)

