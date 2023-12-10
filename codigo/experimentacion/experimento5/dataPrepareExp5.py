import re
import random 

def parseBook(input_file_path, output_file_path):
    with open(input_file_path, 'r', encoding='utf-8') as file:
        content = file.read()

    words_only = re.findall(r'\b[a-zA-Z]+\b', content)
    lowercase_words = [word.lower() for word in words_only]

    lowercase_content = '\n'.join(lowercase_words)

    with open(output_file_path, 'w', encoding='utf-8') as file:
        file.write(lowercase_content)

def select_unique_random_words(input_file_path, output_file_path, number_of_words):
    
    with open(input_file_path, 'r', encoding='utf-8') as file:
        words = file.read().splitlines()

    unique_words = list(set(words))

    selected_words = random.sample(unique_words, min(number_of_words, len(unique_words)))

    with open(output_file_path, 'w', encoding='utf-8') as file:
        file.write('\n'.join(selected_words))


parseBook('dracula.txt', 'draculaParsed.txt')
select_unique_random_words('draculaParsed.txt', 'randomWordsDracula.txt', 10)