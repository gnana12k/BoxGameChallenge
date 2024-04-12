/****************************************************************************
 * File Details
 * ------------
 * File Name: box_game.cpp
 ****************************************************************************
 *
 *  File Description : This file  contains the mechanics of a simple game
 *                     of boxes between two players and unit test cases covered
 *
 ****************************************************************************/
#if 1
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <numeric>
#include <vector>
#include <climits>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
using namespace std;

enum class Color {
	GREEN,
	BLUE
};

class Box
{
      public:
	explicit Box(double initial_weight) : weight_(initial_weight)
	{
	}
	static std::unique_ptr<Box> makeGreenBox(double initial_weight);
	static std::unique_ptr<Box> makeBlueBox(double initial_weight);
	bool operator<(const Box &rhs) const
	{
		return weight_ < rhs.weight_;
	}
        // TODO- DONE
	double absorbWeightAndCalculateScore(double weight)
	{
		double score = 0.0;
		if (color == Color::GREEN) // Green's absorption
		{
			double totalWeight;
			if (inputWeightList.size() == 0) {
				score = weight * weight;
				inputWeightList.push_back(weight);
			} else {
				inputWeightList.push_back(weight);
				int count = static_cast<int>(inputWeightList.size());

				/*if count is less than 3, retain the same value in count, if not
			    get the last 3 elements of vector */
				if (count > 3) {
					count = 3;
				}
				for (int i = inputWeightList.size() - 1;
				     i >=
				     std::max(0, static_cast<int>(inputWeightList.size()) - count);
				     --i) {
					totalWeight += inputWeightList[i];
				}
				double mean = totalWeight / count;
				score = mean * mean;
			}
		} else // Blue's absorption
		{
			double smallest = INT_MAX;
			double largest = INT_MIN;
			if (inputWeightList.size() == 0) // absorbing very first token
			{
				smallest = largest = weight;
				inputWeightList.push_back(weight);
			} else {
				inputWeightList.push_back(weight);
				/*get the min weight from the vector*/
				for (int i = 0; i < inputWeightList.size(); i++) {
					smallest = std::min(
						smallest, static_cast<double>(inputWeightList[i]));
				}
				/*get the max weight from the vector*/
				for (int i = 0; i < inputWeightList.size(); i++) {
					largest = std::max(largest,
							   static_cast<double>(inputWeightList[i]));
				}
			}
			score = ((smallest + largest) * (smallest + largest + 1) / 2) +
				largest; // Cantor's pairing function - pair(smallest,largest)
		}
		weight_ += weight;
		return score;
	}
	void setColor(Color c);
      protected:
	double weight_;
	Color color; // Enum for differentating between boxes
	std::vector<double> inputWeightList;
};

void Box ::setColor(Color c) // setting color of the box
{
	color = c;
}

std::unique_ptr<Box> Box ::makeGreenBox(double initial_weight)
{
	std::unique_ptr<Box> box(new Box(initial_weight));
	box->setColor(Color::GREEN); // make the box GREEN
	return box;
}
std::unique_ptr<Box> Box ::makeBlueBox(double initial_weight)
{
	std::unique_ptr<Box> box(new Box(initial_weight));
	box->setColor(Color::BLUE); // make the box BLUE
	return box;
}

class Player
{
      public:
	void takeTurn(uint32_t input_weight, const std::vector<std::unique_ptr<Box>> &boxes)
	{
		// TODO-
	}
	double getScore() const
	{
		return score_;
	}

      private:
	double score_{0.0};
};

std::pair<double, double> play(const std::vector<uint32_t> &input_weights)
{
	std::vector<std::unique_ptr<Box>> boxes;
	boxes.emplace_back(Box::makeGreenBox(0.0));
	boxes.emplace_back(Box::makeGreenBox(0.1));
	boxes.emplace_back(Box::makeBlueBox(0.2));
	boxes.emplace_back(Box::makeBlueBox(0.3));

	// TODO
	Player player_A;
	Player player_B;
	short A_player_turn = 1; // used to toggle between player A and player B

	for (auto it = input_weights.begin(); it != input_weights.end(); it++) {
		A_player_turn == 1 ? player_A.takeTurn(*it, boxes) : player_B.takeTurn(*it, boxes);
		A_player_turn = A_player_turn ^ 1;
	}
	std::cout << "Scores: player A " << player_A.getScore() << ", player B "
		  << player_B.getScore() << std::endl;
	return std::make_pair(player_A.getScore(), player_B.getScore());
}

TEST_CASE("Final scores for first 4 Fibonacci numbers", "[fibonacci4]")
{
	std::vector<uint32_t> inputs{1, 1, 2, 3};
	auto result = play(inputs);
	REQUIRE(result.first == 13.0);
	REQUIRE(result.second == 25.0);
}

TEST_CASE("Final scores for first 8 Fibonacci numbers", "[fibonacci8]")
{
	std::vector<uint32_t> inputs{1, 1, 2, 3, 5, 8, 13, 21};
	auto result = play(inputs);
	REQUIRE(result.first == 155.0);
	REQUIRE(result.second == 366.25);
}

TEST_CASE("Test absorption of green box", "[green]")
{
	
}

TEST_CASE("Test absorption of blue box", "[blue]")
{

}
#endif
