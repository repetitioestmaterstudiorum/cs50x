import csv
import sys

# ---


def main():
    # cli hint on usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # read database into a dict as {"name": "01234567"} (concat STRs)
    csv_data = {}
    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            strs = reader.fieldnames[1:]
            dna_data = ''.join([row[s] for s in strs])
            csv_data[dna_data] = row["name"]
    
    # read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        sequence_file = file.read()

    # find longest match of each STR in DNA sequence
    dna_data_arr = [longest_match(sequence_file, s) for s in strs]

    # check database for matching profiles
    dna_data = ''.join([str(d) for d in dna_data_arr])

    # print match
    try:
        print(csv_data[dna_data])
    except:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

# execute: python dna.py databases/large.csv sequences/5.txt
# check50 cs50/problems/2022/x/dna
# submit50 cs50/problems/2022/x/dna