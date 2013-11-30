mass = 9855

masses = []
masses.append(57);
masses.append(71);
masses.append(87);
masses.append(97);
masses.append(99);
masses.append(101);
masses.append(103);
masses.append(113);
masses.append(114);
masses.append(115);
masses.append(128);
masses.append(129);
masses.append(131);
masses.append(137);
masses.append(147);
masses.append(156);
masses.append(163);
masses.append(186);

spisok = []
i = 0
for i in range(mass+1):
    spisok.append( 0)

for i in range(mass + 1):
    for j in range(len(masses)):
        if (i - masses[j] > 0):
            if (spisok[i - masses[j]] != 0):
                spisok[i] += spisok[i - masses[j]]
        else:
            if (i - masses[j] == 0):
                spisok[i] += 1
            
print spisok[mass]
