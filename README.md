# Mail-It

##Kompilieren unter Linux
Man benötigt einen c++17-Compiler und Meson. Alle dependencies(nana, sqlite, csv, mailclient, json, inja) müssen in der meson_options.txt angegeben sein. Die Dependencies müssen entsprechend der jeweiligen Dokumentation kompiliert werden. Es müssen auch diverse andere Abhängigkeiten in der jeweiligen Development-Version installiert sein (libcurl, x11, xext, xrandr, glu, gl, xft, fontconfig, sqlite3)

##Kompilieren unter Windows
(nicht erfolgreich)
Mit mingw, meson und gcc. Abhängigkeiten jeweils unter Windows entsprechend der jeweiligen Dokumentation kompilieren. Die Datei meson_options.txt anpassen. 

##Known Bugs
Eigenschaften, die einem Job zugeordnet werden, werden möglicherweise nicht gespeichert.
Das Templating funktioniert nicht zuverlässig bei Variablen aus der Jobdatei.