class Student():
    def __init__(self,name):
        self._name = name
    def getname(self):
        return name

class Boy(Student):
    def __init__(self,name):
        Student.__init__(self,name)
        self._gender = 'boy'
    def getgender(self):
        return self._gender
    def getname(self):
        return self._name
    def getinfo(self):
        return "name:"+self._name+",gender:"+self._gender

s1 = Boy('Sam')
print(s1.getname())
print(s1.getinfo())
