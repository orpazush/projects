#include <vector>   //vector

class Solution
{
public:
    int candy(std::vector<int>& ratings)
    {
        size_t size = ratings.size();
        if (size < 2)
        {
            return 1;
        }

        int *satisfyRight = new int[size];

        satisfyRight[0] = 1;
        size_t leftCandies = 1;
        for (int i = 1; i < size; ++i)
        {
            leftCandies = (ratings[i] > ratings[i-1]) ? leftCandies+1 : 1;
            satisfyRight[i] = leftCandies;
        }

        size_t numOfCandies = leftCandies;
        size_t RightCandies = 1;
        for (int i = size-2; i >= 0; --i)
        {
            RightCandies = (ratings[i] > ratings[i+1]) ? RightCandies+1 : 1;
            numOfCandies += (satisfyRight[i] > RightCandies)
                            ? satisfyRight[i]
                            : RightCandies;
        }

        delete[] satisfyRight;

        return numOfCandies;
    }
};

class Solution
{
public:
    vector<string> getFolderNames(vector<string>& names)
    {
        unordered_map<string, int> numOfnames;
        vector<string> result;
        size_t namesSize = names.size();

        for (size_t i = 0; i < namesSize; ++i)
        {
            auto findNames = numOfnames.find(names[i]);
            if (findNames != numOfnames.end())
            {
                string newName = findNames->first+'('+to_string(findNames->second)+')';
                while (numOfnames.find(newName) != numOfnames.end())
                {
                    ++findNames->second;
                    newName = findNames->first+'('+to_string(findNames->second)+')';
                }
                numOfnames[newName] = 1;
                result.push_back(newName);
            }

            else
            {
                numOfnames[names[i]] = 1;
                result.push_back(names[i]);
            }
        }

        return (result);
    }
};