import matplotlib.pyplot as plt

data = open('data.txt', 'r') #r = reading
number = []
fp = [] #array com a soma de iterações da fila de prioridade sem heap
fp_heap = [] #array com a soma de iterações da fila de prioridade com heap

i = 0 #numero dos x's

# acumulo das iterações
normal = 0
heap = 0

for l in data:
    linha = l.strip()
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
