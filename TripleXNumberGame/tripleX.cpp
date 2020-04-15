#include <iostream>
#include <vector>
#include<string>
#include<math.h>
#include<ctime>


using namespace std;

class TripleNumberHandler
{
public:
	vector<int> numberVector;
	int sum;
	int product;
	int AnswerLimit;
	TripleNumberHandler(int level);
	TripleNumberHandler(vector<int> answer);
	bool compare(TripleNumberHandler comparedTo) {
		if (this->sum == comparedTo.sum && this->product == comparedTo.product)
			return true;
		else
		{
			return false;
		}
	}

private:
	int getProduct(vector<int> numbers) {
		int product = 1;
		for (int i : numbers) {
			product *= i;
		}
		return product;
	}
	int getSum(vector<int> numbers) {
		int sum = 0;
		for (int i : numbers) {
			sum += i;
		}
		return sum;
	}
	vector<int> getNumbersForDifficultyLevel(int level) {

		vector<int> numbers;
		for (int i = 0; i < 3; i++)
		{
			numbers.push_back(generateNumberForLevel(level));
		}
		return numbers;
	}
	int generateNumberForLevel(int level) {
		AnswerLimit = int (pow(level + 1,2));
		return 1 + (rand() % (AnswerLimit));
	}
	int getMax(vector<int> vec)
	{
		int max;
		bool FirstSet{};
		for (int i : vec)
		{
			if (!FirstSet)
			{
				max = i;
				FirstSet = true;
			}
			else
			{
				if (max < i)
					max = i;
			}
		}
		return max;
	}

};
TripleNumberHandler::TripleNumberHandler(int level) {
	numberVector = getNumbersForDifficultyLevel(level);
	product = getProduct(numberVector);
	sum = getSum(numberVector);
};
TripleNumberHandler::TripleNumberHandler(vector<int> answer) {
	numberVector = answer;
	product = getProduct(answer);
	sum = getSum(answer);
	AnswerLimit = getMax(answer);
};
bool fail() {
	std::cout << "You feel feed back from the machine as you are forced out of the cogitator interface.\n\"It seems the machine spirit has rejected you. Say 0 to leave and try again later or 1 to try that level again\""<< std::endl;
	bool TryAgain;
	try
	{
		std::cin >> TryAgain;
	}
	catch (const std::exception&)
	{
		TryAgain = false;
	}
	return TryAgain;
};
void endStatements(bool IsVictorious) {
	if (IsVictorious) {
		std::cout << "You gracefully exit the cogitator and view a tech priest marvel at the glory before you. \n\"I have never seen an acolyte perform so well at the initial phase test! The artifact has produced something the Omnissiah would approve of!\"\nThe tech priest jestures to a perfectly toasted piece of toast that stands erect out of the artifact";
	}
	else {
		std::cout << "\"You have failed the test! Lets try again later.\"";
	}
};
void readOut(TripleNumberHandler question) {
	std::cout << "SUM: ";
	std::cout << question.sum << std::endl;
	std::cout << "PRODUCT: ";
	std::cout << question.product << std::endl;
	std::cout << "THERE ARE ONLY 3 NUMBERS" << std::endl;
	std::cout << "MAX INTEGER LIMIT IS: ";
	std::cout << question.AnswerLimit << std::endl;
}
vector<int> makeGuesses() {
	
	vector<int> Guesses;
	for (int i = 0; i < 3; i++) {
		int guess;
		std::cin >> guess;



		Guesses.push_back(guess);


		
	}
	return Guesses;
}
bool judgeResults(bool IsCorrect) {
	if (IsCorrect)
	{
		return true;
	}
	else
	{
		return fail();
	}
}

int main() {
	srand(time(NULL));
	//Default False
	bool victory{};
	int FinalDifficultyLevel = 5;
	//initial difficulty level
	int DifficultyLevel = 1;

	//cout the initial story. Praise the Omnissiah!
	std::cout << "\"Acolyte, you are to be tested on how you communicated with machine spirites.";
	std::cout << std::endl;
	std::cout << "Most machine spirites do not wish to communicate with dullards so... ";
	std::cout << "\nAnswer whatever questions it asks of you. Otherwise you may upset it.\"\n" << std::endl;

	std::cout << "You connect to the Cogitator and begin to interact with the machine spirit.\n\r\n\r\"If you truly wish to commune with me give the answer to my puzzles.\nThere are three numbers I wish to know. I shall only give you their product and sum.\nYou must tell me the three numbers!\"" << std::endl;
	
	bool Playing = true;
	while (Playing)
	{
		try
		{
			std::cout << "LEVEL: ";
			std::cout << DifficultyLevel << std::endl;
			vector<int> Guesses;
			bool Correct{};
			if (DifficultyLevel == 1)
			{
				vector<int> v{ 3,4,2 };
				TripleNumberHandler Level1(v);

				readOut(Level1);

				Guesses = makeGuesses();
				std::cin.clear();
				std::cin.ignore();

				TripleNumberHandler GuessObj(Guesses);
				

				Correct = GuessObj.compare(Level1);

				Playing = judgeResults(Correct);

			}
			else {
				TripleNumberHandler currentTest(DifficultyLevel);
				readOut(currentTest);
				Guesses = makeGuesses();
				std::cin.clear();
				std::cin.ignore();
				TripleNumberHandler GuessObj(Guesses);
				
				Correct = GuessObj.compare(currentTest);
				Playing = judgeResults(Correct);

			}
			if (Playing && Correct)
			{
				++DifficultyLevel;

			}
			if (Correct && DifficultyLevel > FinalDifficultyLevel)
			{
				victory = true;
				Playing = false;
			}
			
			if(!Playing || DifficultyLevel > FinalDifficultyLevel)
			{
				endStatements(victory);
			}
			Correct = false;
		}
		catch (const std::exception&)
		{
			Playing = false;
			std::cout << "You have failed! Goodbye >:-(";
		}
		

	}
	
	return 0;
}
