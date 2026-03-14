# Overview
I created this simple encoder/decoder for something that I call the Ozymandias code.

The code itself has a few different layers:
- **Substitution cipher**: Letters are replaced with corresponding words from the poem "Ozymandias." The order is just the order that the words appear in the poem (skipping words where the first two letters of the word matches the first two letters of a previously used word).
- **Vigenère cipher**: A more advanced version of the Caesar cipher.
- **Random characters**: Random characters are also added in at certain spots.

The majority of the code is implemented through simple arrays, where the string is broken up into individual characters which are much more easily manipulated. The array is then typically pieced back together into a string after the desired change is applied. This process is repeated over multiple functions, which are run in sequence in order to encode or decode a phrase.

# Design Choices
Of course, this code is not nearly unbreakable so don't use it for anything too important. However, while I am no expert at cryptography, I attempted to make the code as difficult to break as possible while still maintaining it's simplicity and having it be very easy to understand.

The first element I added was the Vigenère cipher, as while it is a classical cipher and easy to break in the modern day I found it easy to understand while not being as trivial as something like a basic Caesar cipher, which fit my purposes very well.

However, I felt this cipher by itself would be too easy to break. I wanted to appy multiple ciphers in layers. However, doing something like applying similar cipher continuously would be akin to just changing the shift of the Vigenère cipher, which doesn't fulfill the purpose I wanted. It also wouldn't add any complexity and the difficulty would be relatively the same. I decided a substitution cipher in which the letters were changed out for longer words could be nice, as it could make short phrases which are easily identifiable harder to find out. I used the Ozymandius poem for this. Identifying the words with only the first letter wouldn't work because there isn't a unique word in the poem for each letter of the alphabet, so I decided to use the first two letters instead.

Finally, adding in characters at specific intervals. I added this in to attempt to foil frequency analysis, which is a common method used to break codes. I created a function that adds in random letters at specified intervals (eg. every second letter) and applied it a few times.

## Implementation Approach

- **Character manipulation**: Uses char arrays for efficient character-by-character processing
- **Pipeline architecture**: Each encryption layer is a separate function, applied sequentially
- **Data structures**: Primarily arrays and String objects for simplicity

For the substitution cipher, I seperated the first two letters in order to identify what word was first, and then skipped characters until the word was over. I would then look at the next two letters and repeat continuously until the entire phrase was decoded. The encoding process was simple, with just identifying the letter and adding in the word from the corresponding location in an array of all the words used.
