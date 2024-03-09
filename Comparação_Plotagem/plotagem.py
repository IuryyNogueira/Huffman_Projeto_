import matplotlib.pyplot as plt

data = open('data.txt', 'r')
number = []
fp = []
fp_heap = []

i = 1

for linha in data:
    linha = linha.strip()
    normal, heap = linha.split(' ')

    number.append(i)
    fp.append(int(normal))
    fp_heap.append(int(heap))
    i += 1  # increment the counter

# Plot the data
plt.plot(number, fp, label='Normal')
plt.plot(number, fp_heap, label='Heap')

# Add labels and title
plt.xlabel('Number')
plt.ylabel('Value')
plt.title('Plot of Data')

# Add a legend
plt.legend()

# Display the plot
plt.tight_layout()
plt.show()