#include <StringLib.h>;
#include <Wire.h> 

const char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

const String fruitsnacks[27] = {"🍈", "🍉", "🍊", "🍏", "🍐", "🍓", "🥥", "🫒", "🌽", "🍋‍🟩", "🍌", "🍒", "🍋", "🍇", "🥑", "🫑", "🍑", "🍍", "🥭", "🍄", "🍅", "🥕", "🫐", "🥝", "🧅", "🥔", "🫚"};

const String ozymandias[27] = {"met", "traveller", "from", "antique", "land", "who", "two", "vast", "legs", "stone", "desert", "near", "them", "half", "sunk", "shattered", "visage", "lies", "wrinkled", "lip", "sneer", "cold", "sculptor", "passions", "pedestal", "name", "ozymandias"};

char encoder[26][26];

void CreateVigenereEncoder(String codeword)
{
  // split code word into an array
  int codewordLength = codeword.length();
  char codewordSplit[codewordLength + 1];
  codeword.toCharArray(codewordSplit, codewordLength + 1);

  // create 2d encoder array
  for (int listPositionEncoder = 0; listPositionEncoder < 26; listPositionEncoder++)
  {
    // find shift and convert to number
    int keyIndex = listPositionEncoder % codewordLength;
    int shift = codewordSplit[keyIndex] - 'a';

    // create row, with the row beginning with the corresponding letter of the key word
    for (int charNum = 0; charNum < 26; charNum++) 
    { 
      encoder[listPositionEncoder][charNum] = alphabet[(charNum + shift) % 26]; 
    }
  }

  // print the encoder
  // for (int rowNum = 0; rowNum < 26; rowNum++)
  // {
  //   for (int columnNum = 0; columnNum < 26; columnNum++) 
  //   { 
  //     Serial. print(encoder[rowNum][columnNum]); 
  //   }
  //   Serial.println();
  // }
}

String AddRandomCharactersToString(String oldWord, int numInsert)
{
  String newWord = "";

  // iterate through the entirety of the word
  for (int i = 0; i < oldWord.length(); i++) 
  {
    newWord += oldWord[i];

    // uses modulus to find if on a place where characters should be added
    if ((i+1) % numInsert == 0 && i != oldWord.length() - 1) 
    { 
      int randgen = random(0, 27);
      if (randgen < 27) { newWord += alphabet[random(0, 26)]; }
      else { newWord += " "; }
    }
  }

  return newWord;
}

String RemoveRandomCharactersFromString(String oldWord, int numInsert)
{
  String newWord = "";
  int count = 0;

  // iterate through the entirety of the word
  for (int i = 0; i < oldWord.length(); i++) 
  {
    count++;

    // uses modulus to find if on a place where characters should not be added
    if (count % (numInsert + 1) != 0)
    {
      newWord += oldWord[i];
    }
  }
  return newWord;
}

String EncryptVigenere(String stringToEncrypt, String key) 
{
  // turns the original word into a character array (with all characters lowercase) so we can go through it 
  int stringToEncryptLength = stringToEncrypt.length(), keyIndex = 0;
  char stringToEncryptSplit[stringToEncryptLength + 1];
  stringToEncrypt.toCharArray(stringToEncryptSplit, stringToEncryptLength + 1);
  key.toLowerCase();

  String encryptedString = "";

  // look through all characters in the character array
  for (int i = 0; i < stringToEncrypt.length(); i++)
  {
      char character = stringToEncryptSplit[i];

      // shift the character forwards a specific amount based on what letter of the key we are on
      if (character >= 'a' && character <= 'z') 
      {
        int shift = key[keyIndex % key.length()] - 'a';
        encryptedString += alphabet[(character - 'a' + shift) % 26];
        keyIndex++; 
      }
      else { encryptedString += character; }
  }
  return encryptedString;
}

String DecryptVigenere(String stringToDecrypt, String key)
{
  // turns the original word into a character array (with all characters lowercase) so we can go through it 
  int stringToDecryptLength = stringToDecrypt.length(), keyIndex = 0;
  char stringToDecryptSplit[stringToDecryptLength + 1];
  stringToDecrypt.toCharArray(stringToDecryptSplit, stringToDecryptLength + 1);
  key.toLowerCase();
  String decryptedString = "";

  // look through all characters in the character array
  for (int i = 0; i < stringToDecryptLength; i++)
  {
    char character = stringToDecryptSplit[i];

    // shift the character backwards a specific amount based on what letter of the key we are on
    if (character >= 'a' && character <= 'z')
    {
      int shift = key[keyIndex % key.length()] - 'a';
      int decryptedCharNum = (character - 'a' - shift + 26) % 26;
      decryptedString += alphabet[decryptedCharNum];
      keyIndex++;
    }
    else { decryptedString += character; }
  }

  return decryp=tedString;
}

String EncryptOzymandius(String stringToEncrypt)
{
  // create a string builder so that each subsequent word can be added on
  StringBuilder<64> strBuilder;
  
  // convert original string to a character array to access all of the characters in it
  int stringToEncryptLength = stringToEncrypt.length();
  char stringToEncryptSplit[stringToEncryptLength + 1];
  stringToEncrypt.toCharArray(stringToEncryptSplit, stringToEncryptLength + 1);

  String encryptedString = "";
  Serial.println();

  // go through each character in the original word
  for (int i = 0; i < stringToEncryptLength; i++)
  {
    char character = stringToEncryptSplit[i];

    // add in the word at the same index of the character, if there is no match (character is a symbol) just add in the character without changing anything
    if (character >= 'a' && character <= 'z') 
    { 
      const char* toAdd = (ozymandias[(character - 'a') % 26]).c_str();
      strBuilder.append(toAdd); 
      encryptedString = strBuilder;
      Serial.print(character); Serial.print("/"); Serial.print(ozymandias[(character - 'a') % 26]); Serial.print("/"); Serial.print(encryptedString);
      Serial.println();
    } 
    else 
    { 
      strBuilder.append(character); 
      encryptedString = strBuilder;
    }
  }

  return encryptedString;
}

String DecryptOzymandias(String stringToDecrypt)
{
  // convert the string to decrypt into a character array to read more easily
  Serial.println();
  int stringToDecryptLength = stringToDecrypt.length(), letterOn = 0;
  char stringToDecryptSplit[stringToDecryptLength + 1];
  stringToDecrypt.toCharArray(stringToDecryptSplit, stringToDecryptLength + 1);

  String decryptedString = "";

  // go until variable letterOn exceeds the length of the string to decrypt
  while (letterOn < stringToDecryptLength)
  {
    // get the first two characters starting from the current position and add them to a string
    String firstTwoLettersKey;
    firstTwoLettersKey += stringToDecryptSplit[letterOn];
    firstTwoLettersKey += stringToDecryptSplit[letterOn + 1];

    // look through each word in the ozymandias list to compare the first two letters
    for (int i = 0; i < 26; i++)
    {
      // get the first two letters of the specific word in the ozymandias list
      String ozymandiasWord = ozymandias[i], ozymandiasFirstTwo;
      int ozymandiasWordLength = stringToDecrypt.length();
      char ozymandiasSplit[ozymandiasWordLength + 1];
      ozymandiasWord.toCharArray(ozymandiasSplit, ozymandiasWordLength + 1);
      ozymandiasFirstTwo += ozymandiasSplit[0];
      ozymandiasFirstTwo += ozymandiasSplit[1];

      // compare the two and add to decrypted string to return if they match
      if (ozymandiasFirstTwo == firstTwoLettersKey) 
      { 
        Serial.print(ozymandiasFirstTwo); Serial.print(" -> "); Serial.print(ozymandias[i]); Serial.print(ozymandias[i].length()); Serial.print(alphabet[i]); Serial.println(letterOn);
        decryptedString = decryptedString + alphabet[i];

        letterOn += ozymandias[i].length();
      }
    }
  }

  return decryptedString;
}

String EncryptFruitSnack(String stringToEncrypt)
{
  int stringToEncryptLength = stringToEncrypt.length(), keyIndex = 0;
  char stringToEncryptSplit[stringToEncryptLength + 1];
  stringToEncrypt.toCharArray(stringToEncryptSplit, stringToEncryptLength + 1);

  String encryptedString = "";

  for (int i = 0; i < stringToEncrypt.length(); i++)
  {
    int letterStor = 26;
    char character = stringToEncryptSplit[i];
    for (int letters = 0; letters < 26; letters++)
    {
      if (character == alphabet[letters])
      {
        letterStor = letters;
      }
    }
      
    encryptedString += fruitsnacks[letterStor];
  }

  return encryptedString;
}

String DecryptFruitSnack(String s)
{
  return " ";
}

String EncryptString(String stringToEncrypt, String key, int insertRandom = -1, int insertRandom2 = -1, int insertRandom3 = -1)
{
  Serial.println("Original text"); Serial.println(stringToEncrypt);

  String encryptedString = stringToEncrypt;

  // add in random letters at specified places
  if (insertRandom != -1) 
  { 
    encryptedString = AddRandomCharactersToString(encryptedString, insertRandom);
    Serial.println(); Serial.println("Added in random letters"); Serial.println(encryptedString);
  }

  encryptedString = EncryptOzymandius(encryptedString);
  Serial.println(); Serial.println("Turned letters into words"); Serial.println(encryptedString);

  // add in random letters at specified places
  if (insertRandom2 != -1) 
  { 
    encryptedString = AddRandomCharactersToString(encryptedString, insertRandom2);
    Serial.println(); Serial.println("Added in random letters"); Serial.println(encryptedString);
  }

  encryptedString = EncryptVigenere(encryptedString, key);
  Serial.println(); Serial.println("Encrypted with Vigenere"); Serial.println(encryptedString);

  // add in random letters at specified places
  if (insertRandom3 != -1) 
  { 
    encryptedString = AddRandomCharactersToString(encryptedString, insertRandom3);
    Serial.println(); Serial.println("Added in random letters"); Serial.println(encryptedString);
  }

  //encryptedString = EncryptFruitSnack(encryptedString);
  //Serial.println(); Serial.println("Converted into fruit snacks"); Serial.println(encryptedString);

  return encryptedString;
}

String DecryptString(String stringToDecrypt, String key, int insertRandom = -1, int insertRandom2 = -1, int insertRandom3 = -1)
{
  String decryptedString = stringToDecrypt;

  Serial.println("Encrypted text"); Serial.println(decryptedString);

  //decryptedString = DecryptFruitSnack(decryptedString);
  //Serial.println("Converted from fruit snacks to normal text"); Serial.println(decryptedString);

  // remove random letters
  if (insertRandom3 != -1) 
  { 
    decryptedString = RemoveRandomCharactersFromString(decryptedString, insertRandom3); 
    Serial.println(); Serial.println("Removed random letters"); Serial.println(decryptedString);
  }

  decryptedString = DecryptVigenere(decryptedString, key);
  Serial.println(); Serial.println("Decrypted Vigenere"); Serial.println(decryptedString);

  // add in random letters at specified places
  if (insertRandom2 != -1) 
  { 
    decryptedString = RemoveRandomCharactersFromString(decryptedString, insertRandom2);
    Serial.println(); Serial.println("Removed random letters"); Serial.println(decryptedString);
  }

  decryptedString = DecryptOzymandias(decryptedString);
  Serial.println(); Serial.println("Translated words into letters"); Serial.println(decryptedString);

  // add in random letters at specified places
  if (insertRandom != -1) 
  { 
    decryptedString = RemoveRandomCharactersFromString(decryptedString, insertRandom);
    Serial.println(); Serial.println("Removed random letters"); Serial.println(decryptedString);
  }

  return decryptedString;
}

void setup() 
{
  Serial.begin(9600);
  Wire.begin(9);
  wire.onRecieve(recieveEvent)

  String key = "fruitsnacks";
  int position = 2; int position2 = 3; int position3 = 2;
  
  Serial.println();

  // String encryptedString = AddRandomCharactersToString("add new words to this", position);
  // Serial.println(encryptedString);
  // encryptedString = AddRandomCharactersToString(encryptedString, position2);
  // Serial.println(encryptedString);
  // encryptedString = AddRandomCharactersToString(encryptedString, position3);
  // Serial.println(encryptedString);
  // String encryptedString = EncryptString("hi", key, position, position2, position3);
  // Serial.println("-------------------------------------------------------------------------");
  // Serial.println(encryptedString);
  // Serial.println("-------------------------------------------------------------------------");

  // String decryptedString = RemoveRandomCharactersFromString(encryptedString, position3);
  // Serial.println(decryptedString);
  // decryptedString = RemoveRandomCharactersFromString(decryptedString, position2);
  // Serial.println(decryptedString);
  // decryptedString = RemoveRandomCharactersFromString(decryptedString, position);
  // Serial.println(decryptedString);
}

void recieveEvent(int bytes)
{
  String encryptedString = Wire.read();
  String decryptedString = DecryptString(, key, position, position2, position3);
  Serial.println("-------------------------------------------------------------------------");
  Serial.println(decryptedString);
  Serial.println("-------------------------------------------------------------------------");
}

void loop() 
{

}