import numpy as np
import numpy.random as rnd
import matplotlib.pyplot as plt
import subprocess

MIN, MAX = 5, 20
CLOCK_FREQ = 2e9

times = np.array([1000 / CLOCK_FREQ] * (MAX - MIN + 1))
for size in xrange(MIN, MAX + 1):
    outBytes = rnd.randint(0, 256, 1<<size)

    with open("plaintext.txt", "w") as f:
        for b in outBytes:
            f.write((hex(b)[2:-1]).zfill(2))

    times[size - MIN] *= float((subprocess.check_output("savitr_timer e plaintext.txt keys.txt ciphertext.txt")))

fig = plt.figure(1)
plt.semilogx(2**np.arange(MIN, MAX + 1), times, basex=2, linewidth=3)
plt.xlabel("Input file size (bytes)")
plt.ylabel("Encryption time (ms, assuming 2GHz average clock frequency)")
plt.title("SAVITR : File size vs Encyption time")
plt.show()