import matplotlib.pyplot as plt
import numpy as np

data = open('data.txt', 'r')
number = []
fp = []
fp_heap = []

i = 0

normal = 0
heap = 0
for linha in data:
    linha = linha.strip()
    normal_reading_value, heap_reading_value = linha.split(' ') # Lendo valores do arquivo

    # Somando valores para acumular em normal e heap, para comparar a evolução
    normal += int(normal_reading_value)
    heap += int(heap_reading_value)

    # Colocando os valores em seus respectivos arrays
    number.append(i)
    fp.append(int(normal))
    fp_heap.append(int(heap))
    i += 1  # Incrementando o contador

data.close()  # Fechar o arquivo

# Plotando a evolução das somas à medida que os números são deletados
plt.plot(number, fp, label='Normal')
plt.plot(number, fp_heap, label='Heap')

# Adicionando rótulos e título
plt.xlabel('Numbers deleted')
plt.ylabel('Cumulative iterations')
plt.title('Cumulative Iterations as Numbers Deleted Increase')

# Adicionando uma legenda
plt.legend()

# Exibindo o gráfico
plt.tight_layout()
plt.grid(True)  # Adiciona uma grade para melhor visualização
plt.show()
