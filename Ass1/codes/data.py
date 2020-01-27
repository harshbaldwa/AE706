with open('file.csv') as f:
    first_line = f.readline()

first_line = first_line.replace('\n', '')
first_line = first_line.strip()
name = first_line + '.txt'

with open('file.csv') as f:
    with open('../data/'+name, "w") as f1:
        for line in f:
            f1.write(line)
