import matplotlib.pyplot as plt
import numpy as np

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

data.close()  # Close the file

# Calculate cumulative sums
fp_cumsum = np.cumsum(fp)
fp_heap_cumsum = np.cumsum(fp_heap)

# Plot the cumulative sums
plt.plot(number, fp_cumsum, label='Normal')
plt.plot(number, fp_heap_cumsum, label='Heap')

# Add labels and title
plt.xlabel('Numbers deleted')
plt.ylabel('iterations')
plt.title('priority queue with and without heap')

# Add a legend
plt.legend()

# Display the plot
plt.tight_layout()
plt.show()
