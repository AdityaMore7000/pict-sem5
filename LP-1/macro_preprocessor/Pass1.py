class Pass1:
    def __init__(self) -> None:
        self.count_pp = 0
        self.count_kp = 0
        self.mnt = ""
        self.pntab = ""
        self.mdtp = 1
        self.kptp = 1
        self.kpdt = ""
        self.macro_count = 0
        self.ic = ""
        self.mdt = ""
        pass

    def process(self):
        NEXT_MACRO = False
        IS_START = False
        with open("LP-1/macro_preprocessor/source.asm", "r") as file:
            data = file.readlines()
            for lines in data:
                if lines.find('START') != -1 or IS_START == True:
                    self.ic += lines
                    IS_START = True

                else:
                    word = lines.replace("&", "").replace(",", "").split()
                    if NEXT_MACRO == True:
                        self.count_kp = 0
                        self.count_pp = 0
                        macro_name = word[0]
                        self.pntab += f"{macro_name}\t"
                        for i in range(1, len(word)):
                            if word[i].find("=") != -1:
                                self.count_kp += 1
                                parameter_name = word[i].partition("=")[0]
                                given_name = word[i].partition('=')[2]
                                self.pntab += parameter_name + "\t"
                                self.kpdt += f"{parameter_name}\t{given_name}\n"
                            else:
                                self.pntab += word[i] + "\t"
                                self.count_pp += 1
                        self.pntab += "\n"
                        self.mnt += f"{macro_name}\t{self.count_pp}\t{self.count_kp}\t{self.mdtp}\t{self.kptp}\n"
                        self.kptp += self.count_kp
                        NEXT_MACRO = False

                    elif word[0] == 'MACRO':
                        self.macro_count += 1
                        NEXT_MACRO = True
                        pass

                    else:
                        string = word[0] + "\t"
                        parameters = self.pntab.split(
                            '\n')[self.macro_count-1].split()
                        for i in range(1, len(word)):
                            if word[i].find('=') != -1:
                                string += word[i] + "\t"
                            else:
                                index = parameters.index(word[i])
                                string += f"(P,{index})\t"
                        self.mdtp += 1
                        string += "\n"
                        self.mdt += string

        print("*"*8 + "MDT" + "*"*8)
        print(self.mdt)
        print("*"*8 + "MNT" + "*"*8)
        print(self.mnt)
        print("*"*8 + "PNTAB" + "*"*8)
        print(self.pntab)
        print("*"*8 + "KPDT" + "*"*8)
        print(self.kpdt)
        print("*"*8 + "IC" + "*"*8)
        print(self.ic)


test = Pass1()
test.process()
