class Pass2:
    # INPUT TO PASS 2 IS intermediate.txt and mdt.txt
    def __init__(self) -> None:
        self.mnt = {}
        self.pntab = {}
        self.kpdt = {}
        self.output = ""
        self.aptab = {}
        self.current_macro = 0
        pass

    def readFiles(self):
        self.mnt = {
            'M1':      [2,       2,      1,       1],
            'M2':      [2,       2,       6,       3]
        }

        self.pntab = {
            'M1':     ['X',       'Y',       'A',       'B'],
            'M2':      ['P',       'Q',       'U',      'V']
        }

        self.kpdt = {
            'A':  'AREG',
            'B':    '',
            'U': 'CREG',
            'V': 'DREG'
        }

        pass

    def process(self):
        icFile = open(
            "LP-1/macro_preprocessor/intermediate.txt", "r")

        mdtFile = open(
            "LP-1/macro_preprocessor/mdt.txt", "r")

        for lines in icFile:
            word = lines.replace(",", "").replace("&", "").split()
            if word[0] not in self.mnt.keys():
                self.output += lines
            else:
                self.current_macro += 1
                self.aptab = {}
                MNT = self.mnt[word[0]]
                pp = MNT[0]
                kp = MNT[1]
                for i in range(1, pp+1):
                    self.aptab[i] = word[i]

                # HERE MAKE SURE WE PASS ALL THE PARAMETERS
                # TODO: Mapping of KEYWORD parameters is not done

                for i in range(pp+1, pp+kp+1):
                    if word[i].partition("=")[2] == '':
                        self.aptab[i] = self.kpdt[word[i].partition('=')[0]]
                    else:
                        self.aptab[i] = word[i].partition("=")[2]

                for lines in mdtFile:
                    wordMDT = lines.split()
                    if wordMDT[0] != 'MEND':
                        self.output += wordMDT[0] + "\t"

                        for i in range(1, len(wordMDT)):
                            if wordMDT[i].find('=') == -1:
                                parameter_index = int(wordMDT[i][3])
                                self.output += self.aptab[parameter_index] + "\t"
                            else:
                                self.output += wordMDT[i] + "\t"

                        self.output += "\n"

                    else:
                        break

                # print(self.aptab)

        print(self.output)


test = Pass2()
test.readFiles()
test.process()
