/*

    Important: This code contains bugs and not finished yet, I will update it soon.

*/

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <cctype> 
#include <vector>

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

    // Remove words punctuation and transform it to lower case
    std::string cleanWord(const std::string& word) const {
        std::string cleanedWord; 
        for (int i = 0; i < word.length(); ++i) { // loop through the word
            if(word[i] >= 'a' && word[i] <= 'z' || word[i] >= 'A' && word[i] <= 'Z') { // keep alphabetic characters
                cleanedWord += std::tolower(word[i]); // transform to lowercase
            }
        }
        return cleanedWord; // return cleanedWord
    }

    bool isStopWord(const std::string& word) const {
        return stopWords.find(word) != stopWords.end();
    }

public:

    // Breakdown sentence into the chunks
    std::vector<std::string> ProcessAndTokenizeText(const std::string& text) const {
        std::vector<std::string> ProcessedAndTokenizeWords; // Array of Cleaned words
        std::string chunk = "";

        for (int i = 0; i < text.length(); ++i) {
            if(text[i] == ' '){
                if(!chunk.empty()){ // exclude empty ProcessedAndTokenizeWords
                    std::string cleanedChunk = cleanWord(chunk); // clean word
                    std::cout << "Debug: cleanedChunk: " << cleanedChunk << std::endl;
                    if(!cleanedChunk.empty() && !isStopWord(cleanedChunk)) { // Assign, if it not a stop word and not empty
                        ProcessedAndTokenizeWords.push_back(cleanedChunk); // push clean ProcessedAndTokenizeWords
                        chunk = "";
                    }
                }
            } else {
                chunk += text[i];
            }
        }

        if(!chunk.empty()){
            ProcessedAndTokenizeWords.push_back(chunk);
        }

        return ProcessedAndTokenizeWords;
    }

};

int main(int argc, const char* argv[]) {

    Utility u;

    if(argc > 1) { // if argument are passed
        for (int i = 1; i < argc; ++i) {
            // write logic for it later
        }
    } else { // if no argument
        // std::string filename;
        // std::cout << "Enter filename: ";
        // std::cin >> filename;
        // std::cout << filename;

        // test text 
        std::string text = "Hello world C++ is a great";
        std::vector<std::string> ProcessedText = u.ProcessAndTokenizeText(text);
        for (auto it = ProcessedText.begin(); it != ProcessedText.end(); ++it){
            std::cout << *it << " ";
        }
    }

    std::map<std::string, int> wordCount;

    return 0;
}