from random import randint

def findArr(arr: list, value: int) -> bool:

    for i in arr:

        if i == value:
            return True

    return False

class File():

    def __init__(self, path: str, name: str, treeType: str) -> None:

        self.__path = path
        self.__name = name
        self.__type = treeType

        self.__dir = ''

    def save(self, data: list) -> None:

        if self.__type == 'BST':
            self.__name += '_BST'

        self.__dir = self.__path + self.__name

        with open(self.__dir, 'w') as f:

            f.write(str(len(data)) + '\n')

            result: str = ''

            for i in data:

                result += str(i) + ' '

            f.write(result + '\n')

            if self.__type == 'AVL':
                f.write('FindMinMax\n')
                f.write('Print\n')
                f.write('Exit')
            elif self.__type == 'BST':
                f.write('Rebalance\n')
                f.write('Exit')

class NumberGenerator():

    def generate(self, n: int, k: int) -> list:

        result: list = []

        number: int = randint(0, k)

        result.append(number)

        for i in range(n - 1):

            while findArr(result, number):
                number: int = randint(0, k)

            result.append(number)

        return result

def main() -> None:

    numberGenerator: NumberGenerator = NumberGenerator()

    path: str = './benchmark_data_trees/'
    name: str = ''

    for i in range(1 , 20):

        name = str(i)
        numbers: list = numberGenerator.generate(pow(2, i) ,pow(2, 20))

        file: File = File(path, name, 'AVL')
        file.save(numbers)

        file0: File = File(path, name, 'BST')
        file0.save(numbers)



if __name__ == "__main__":
    main()