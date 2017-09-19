#coding: utf-8
#!/usr/bin/env python2

import subprocess
import sys

graph_files = [
    ('graph2.g6', 2),
    ('graph3.g6', 4),
    ('graph4.g6', 11),
    ('graph5.g6', 34),
    ('graph6.g6', 156),
    ('graph7.g6', 1044),
    ('graph8.g6', 12346),
    ('graph9.g6', 274668),
    ('graph10.g6', 12005168)
]

def processar(grafo, ini = None, fim = None):
    resultado = open("resultados/" + grafo[0] + ".txt", "w")
    
    if ini is None:
        for idx in range(grafo[1]):
            showg = subprocess.Popen (["./bin/showg", "-Aq", "grafos/" + grafo[0], "-p" + str(idx + 1)], stdout = subprocess.PIPE)
            PFC = subprocess.Popen(["./bin/PFC"], stdin = showg.stdout, stdout = subprocess.PIPE)
            out, err = PFC.communicate()
            resultado.write(out)
    else:
        for idx in range(fim - ini):
            showg = subprocess.Popen (["./bin/showg", "-Aq", "grafos/" + grafo[0], "-p" + str(idx + 1 + ini)], stdout = subprocess.PIPE)
            PFC = subprocess.Popen(["./bin/PFC"], stdin = showg.stdout, stdout = subprocess.PIPE)
            out, err = PFC.communicate()
            resultado.write(out)

    resultado.close()

def main():
    for grafo in graph_files:
        if sys.argv[1] in grafo[0]:
            if len(sys.argv) == 2: processar(grafo)
            else: processar(grafo, sys.argv[2], sys.argv[3])               

if __name__ == '__main__':
    main()