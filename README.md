# apd_trma1

am 3 map_threads => ca fiecae primeste un fisier la inceput, iar cand termina unul, il ia pe urmatorul la rand pana cand nu mai sunt
Struct in care incapaulez id.ul thread.ului map si listele pt numere puteri perfecte. Am nevoie de un vectori de altfel de structuri pt fiecare thread map.
Deci asta.i cam tot, probleme ce pot aparea sunt in nr. de liste si cum sa calculez dc un nr e numar perfect.
Deci pt calcul de perfecte iau fiecare nr de la 2 in sus si io calculez la puterea pana la E+1 dc eu am E = 3 at am exponentii 2, 3 si 4 pe care ii aplic fiecarui nr in parte, pana cand gasesc carui nr corespund si merg de la 2 pana la jumatea nr.uli caruia incerc sa.i gasesc clasificatea in una din liste.
Pt alocarea de fisere la threads map prima data aloc cu un ok pt fiecare thread map cate un fisier, iar apoi cn termina il i.a pe urmat si toto asa cu mutex dc termina si vor sa ia un fisier in acleasi timp, sau pt a nu folosi var s de obtinere nume fisier in acelasi timp, ca sa nu stochez  numele fiserelor intr.un vector.
