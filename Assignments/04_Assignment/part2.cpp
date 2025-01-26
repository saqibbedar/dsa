/*

    This program implemented with bonus task 2 and basic display functionality which prints the word and its frequency. By default, print functionality is commented and program is go with Bonus task 2 which accept argument or if no argument then reads the filename and generates html file as required in bonus task 2.

*/

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <cctype> // For std::tolower and std::isalpha
#include <sstream> // for Tokenization
#include <fstream>

/*
    This class will help us in Text Processing(cases, stop words, punctuations) and Tokenization(word level).
*/
class Utility {
    /*
        Copyright StopWords © larsyencken : https://gist.github.com/larsyencken/1440509
        Freely available stopword list, balancing coverage and size.
        From http://www.lextek.com/manuals/onix/stopwords1.html
    */

    std::set<std::string> stopWords = {
        "a","about", "above", "across", "after", "again", "against", "all", "almost", "alone", "along", "already", 
        "also", "although", "always", "among", "an", "and", "another", "any", "anybody", "anyone", "anything",
        "anywhere", "are", "area", "areas", "around", "as", "ask", "asked", "asking", "asks", "at", "away", "b", 
        "back", "backed", "backing", "backs", "be", "became", "because", "become", "becomes", "been", "before", 
        "began", "behind", "being", "beings", "best", "better", "between", "big", "both", "but", "by", "c", "came",
        "can", "cannot", "case", "cases", "certain", "certainly", "clear", "clearly", "come", "could", "d", "did",
        "differ", "different", "differently", "do", "does", "done", "down", "down", "downed", "downing", "downs",
        "during", "e", "each", "early", "either", "end", "ended", "ending", "ends", "enough", "even", "evenly",
        "ever", "every", "everybody", "everyone", "everything", "everywhere", "f", "face", "faces", "fact", "facts",
        "far", "felt", "few", "find", "finds", "first", "for", "four", "from", "full", "fully", "further", "furthered",
        "furthering", "furthers", "g", "gave", "general", "generally", "get", "gets", "give", "given", "gives", "go",
        "going", "good", "goods", "got", "great", "greater", "greatest", "group", "grouped", "grouping", "groups",
        "h", "had", "has", "have", "having", "he", "her", "here", "herself", "high", "high", "high", "higher", "highest",
        "him", "himself", "his", "how", "however", "i", "if", "important", "in", "interest", "interested", "interesting",
        "interests", "into", "is", "it", "its", "itself", "j", "just", "k", "keep", "keeps", "kind", "knew", "know", 
        "known", "knows", "l", "large", "largely", "last", "later", "latest", "least", "less", "let", "lets", "like",
        "likely", "long", "longer", "longest", "m", "made", "make", "making", "man", "many", "may", "me", "member",
        "members", "men", "might", "more", "most", "mostly", "mr", "mrs", "much", "must", "my", "myself", "n", "necessary",
        "need", "needed", "needing", "needs", "never", "new", "new", "newer", "newest", "next", "no", "nobody", "non",
        "noone", "not", "nothing", "now", "nowhere", "number", "numbers", "o", "of", "off", "often", "old", "older",
        "oldest", "on", "once", "one", "only", "open", "opened", "opening", "opens", "or", "order", "ordered", "ordering",
        "orders", "other", "others", "our", "out", "over", "p", "part", "parted", "parting", "parts", "per", "perhaps",
        "place", "places", "point", "pointed", "pointing", "points", "possible", "present", "presented", "presenting",
        "presents", "problem", "problems", "put", "puts", "q", "quite", "r", "rather", "really", "right", "right", "room",
        "rooms", "s", "said", "same", "saw", "say", "says", "second", "seconds", "see", "seem", "seemed", "seeming",
        "seems", "sees", "several", "shall", "she", "should", "show", "showed", "showing", "shows", "side", "sides",
        "since", "small", "smaller", "smallest", "so", "some", "somebody", "someone", "something", "somewhere", "state",
        "states", "still", "still", "such", "sure", "t", "take", "taken", "than", "that", "the", "their", "them", "then",
        "there", "therefore", "these", "they", "thing", "things", "think", "thinks", "this", "those", "though", "thought",
        "thoughts", "three", "through", "thus", "to", "today", "together", "too", "took", "toward", "turn", "turned",
        "turning", "turns", "two", "u", "under", "until", "up", "upon", "us", "use", "used", "uses", "v", "very", "w",
        "want", "wanted", "wanting", "wants", "was", "way", "ways", "we", "well", "wells", "went", "were", "what",
        "when", "where", "whether", "which", "while", "who", "whole", "whose", "why", "will", "with", "within",
        "without", "work", "worked", "working", "works", "would", "x", "y", "year", "years", "yet", "you", "young",
        "younger", "youngest", "your", "yours", "z"
    };

public:

    bool isStopWord(const std::string& word) const {
        // find return current pointer if value was found and if not then it return the end()
        return stopWords.find(word) != stopWords.end(); // compare both's iterators
    }

    // Remove words punctuation and transform it to lower case and handle mixedcase
    void ProcessChunk(std::string& word) const { // take word by reference
        std::string cleanedWord; 
        for (int i = 0; i < word.length(); ++i) { // loop through the word
            if(std::isalpha(word[i])) { // keep alphabetic characters
                cleanedWord += std::tolower(word[i]); // transform to lowercase
            }
        }
        word = cleanedWord;
    }

    // Bonus Task 2: Instead of displaying the frequencies of the words, generate an HTML file which shows a word cloud. You may use frequency as a measure of font-size and display frequent words in larger font.

    void generateHTMLFile(std::map<std::string, int> &wordCount) const {

        std::ofstream f("index.html"); // create index.html file

        auto it = wordCount.begin();

        f << "<html>" << std::endl << "<title>Word Cloud</title>" << std::endl << "<body>" << std::endl;

            f << "\t<h1 style='width: 100%; text-align: center; margin-top: 30px;'>Default font size is 14px</h1>" << std::endl;
            
            f << "\t<ul>" << std::endl;

            while(it != wordCount.end()){
                // default font size is 14px to for visiblity of word
                f << "\t\t<li " << "style='" << "font-size: " << (14 + it->second) << "px'" << ">" << it->first << "</li>" << std::endl;
                ++it;
            }

            f << "\t</ul>" << std::endl;

        f << "</body>" << std::endl << "</html>"<<std::endl;
    }

};

int main(int argc, const char* argv[]) {

    try
    {

        Utility utility;

        std::map<std::string, int> wordCount; // To store word frequency

        if(argc > 1) { // if argument are passed

            std::ifstream f(argv[1]); // open file

            std::string inputText; // Store text coming from file

            if(f.is_open()) {

                std::string line; // to read text line by line

                while(std::getline(f, line)) {
                    inputText += line; // append the line to inputText 
                }

                f.close(); // close file after reading the text

                std::stringstream chunks(inputText); // set the chunks for tokenization

                std::string chunk; // token

                // Process And Tokenization
                while(chunks >> chunk) { // extract chunk from chunks

                    utility.ProcessChunk(chunk); // process chunk - clean word

                    if(!chunk.empty() && !utility.isStopWord(chunk)) { // if chunk is not empty and also not a stopWord then add it to the map
                        wordCount[chunk]++; // add the key and 
                    }
                }

                // Task 1: Display the frequencies of the word

                // std::cout << "Word frequencies:\n";

                // std::map<std::string, int>::iterator it = wordCount.begin();

                // while(it != wordCount.end()) {
                //     std::cout << it->first << ": " << it->second << std::endl;
                //     ++it;
                // }

                // Bonus Task 2: Generate a HTML file
                utility.generateHTMLFile(wordCount);

            } else {

                throw("Error <file> Unable to open file");

            }

        } else { // if no argument

            // get the filename
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;

            std::ifstream f(filename); // open file

            std::string inputText;

            if(f.is_open()) {

                std::string line; // read text from file line by line

                while(std::getline(f, line)){
                    inputText += line; // append line to inputText
                }; 

                f.close(); // close file after reading the text
                
                std::stringstream chunks(inputText);
                std::string chunk;

                // Process And Tokenization
                while(chunks >> chunk) { // extract chunk from chunks

                    utility.ProcessChunk(chunk); // process chunk

                    if(!chunk.empty() && !utility.isStopWord(chunk)) { // if chunk is not empty and also not a stopWord then add it to the map
                        wordCount[chunk]++; // add the key and 
                    }
                }

                // Task 1: Display the frequencies of the word

                // std::cout << "Word frequencies:\n";
                // std::map<std::string, int>::iterator it = wordCount.begin();
                // while(it != wordCount.end()) {
                //     std::cout << it->first << ": " << it->second << std::endl;
                //     ++it;
                // }

                // Bonus Task 2: Generate a HTML file
                utility.generateHTMLFile(wordCount);

            } else {

                throw("Error <file> Unable to open file");

            }

        }
    }

    catch(const char* error)
    {
        std::cerr << error << std::endl;
    }
    
    return 0;
}