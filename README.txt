Predi Dragos 311 CC tema 3 

Problema 1:
Pentru retinerea datelor am creat un vector de cuvinte in care am adaugat toti actorii unici. Indexul in vector reprezenta id-ul actorului in graful meu.

!!!Pentru toate implementarile de algoritm m-am inspirat si de pe internet, in principal de pe GeeksForGeeks. Nu am copiat cod efectiv (implementarile lor sunt oricum in C++) dar cel putin pentru algoritmul lui Tarjan si Djisktra am cam urmat pas cu pas ce fac ei acolo !!!

Pentru primul task am inceput un DFS din fiecare nod nevizitat, fiecare apel al functiei reprezinta un elem conex
Pentru al doilea task am folosit un BFS si un vector de distante in care memoram distanta de la nodul de start la orice nod din graf
Pentru al treilea task am folosit algoritmul lui Tarjan

Pentru bonus am incercat sa implementez rapid algoritmul lui Bronn Kerbosch dar nu am mai avut timp sa folosesc o structura de date potrivita pentru cuvinte si primesc timeout

Problema 2:
Am folosit algoritmul lui Djisktra tinand cont si de gardieni. La fiecare pas, verificam pentru fiecare nod daca exista gardieni la timpul respectiv si updatam distantele in mod conformant.