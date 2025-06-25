class Person:
    def __init__(self, name, age, univ):
        self.name = name
        self.age = age
        self.univ = univ
    
    def show(self):
        print(self.name, self.age, self.univ)

    def information(self, name):
        self.name = name

bomin = Person('spring', 25, 'Ewha')
bomin.show()
