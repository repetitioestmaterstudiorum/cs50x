from cs50 import get_string

# ---


def main():
    # text to analyze
    text = get_string("Text: ")

    # counting
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # calculate averages
    avg_letters_100_words = letters / words * 100
    avg_sentences_100_words = sentences / words * 100

    # calculate index
    index = 0.0588 * avg_letters_100_words - 0.296 * avg_sentences_100_words - 15.8
    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {round(index)}")


def count_letters(text):
    return sum([1 for char in text if char.isalpha()])


def count_words(text):
    return sum([1 for char in text if char == ' ']) + 1


def count_sentences(text):
    end_of_sentences = ['.', '!', '?']
    return sum([1 for char in text if char in end_of_sentences])


main()

# check50 cs50/problems/2022/x/sentimental/readability
# submit50 cs50/problems/2022/x/sentimental/readability