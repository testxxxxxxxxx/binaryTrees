from random import randint

def findArr(arr: list, value: int) -> bool:

    for i in arr:

        if i == value:
            return True

    return False

class File():

    def __init__(self, path: str, name: str) -> None:

        self.__path = path
        self.__name = name
        self.__dir = path + name

    def save(self, data: list) -> None:

        with open(self.__dir, 'w') as f:

            f.write(str(len(data)) + '\n')

            result: str = ''

            for i in data:

                result += str(i) + ' '

            f.write(result)

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

    for i in range(1 , 18):

        name = str(i)
        numbers: list = numberGenerator.generate(pow(2, i) ,pow(2, 17))

        file: File = File(path, name)
        file.save(numbers)

if __name__ == "__main__":
    main()