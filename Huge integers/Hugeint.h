#pragma once
#include<string>
#include<vector>
#include<iostream>
class Hugeint
{
	std::string m_hugint;

	void correction(std::string& st)const;
	friend std::ostream& operator << (std::ostream& out, const Hugeint& ob);
public:
	Hugeint(std::string value);
	Hugeint(int value);
	bool operator <=(const Hugeint& arg)const;
    bool operator <(const Hugeint& arg)const;
	bool operator ==(const Hugeint& arg)const;

	Hugeint operator + (const Hugeint& arg)const;
    Hugeint operator - (const Hugeint& arg)const;

    Hugeint operator * (const Hugeint& arg)const;
	Hugeint operator / (const Hugeint& arg)const;
	Hugeint& operator = (const Hugeint& arg);


};

inline void Hugeint::correction(std::string& st)const 
{
	int k = 0;
	for (int i = 0; i < st.size(); ++i)
	{
		if (st.at(i) == '0')
		{
			++k;
		}
		else
		{
			break;
		}
	}
	if (k > 0)
	{
		st.erase(st.begin(), st.begin() + k);
	}

}

inline Hugeint::Hugeint(std::string value)
{
	this->correction(value);
	for (int i = 0; i < value.size(); ++i)
	{
		if (value.at(i) < '0' || value.at(i) > '9')
		{
			std::cout << "your string is not number" << std::endl;
			std::abort();
		}
	}
	m_hugint = value;
}

inline Hugeint::Hugeint(int value):m_hugint(std::to_string(value)){}

inline bool Hugeint::operator<=(const Hugeint& arg) const
{
	if (this->m_hugint.size() < arg.m_hugint.size())
	{
		return true;
	}
	else if(this->m_hugint.size() > arg.m_hugint.size())
	{
		return false;
	}
	for (int i = 0; i < m_hugint.size(); ++i)
	{
		if (m_hugint.at(i) < arg.m_hugint.at(i))
		{
			return true;
		}
		else if (m_hugint.at(i) > arg.m_hugint.at(i))
		{
			return false;
		}
	}
	return true;
}

inline bool Hugeint::operator<(const Hugeint& arg) const
{
	if (this->m_hugint.size() < arg.m_hugint.size())
	{
		return true;
	}
	else if (this->m_hugint.size() > arg.m_hugint.size())
	{
		return false;
	}
	for (int i = 0; i < m_hugint.size(); ++i)
	{
		if (m_hugint.at(i) < arg.m_hugint.at(i))
		{
			return true;
		}
		else if (m_hugint.at(i) > arg.m_hugint.at(i))
		{
			return false;
		}
	}
	return false;
}

inline bool Hugeint::operator==(const Hugeint& arg) const
{
	if (arg.m_hugint.size() != this->m_hugint.size())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < this->m_hugint.size(); ++i)
		{
			if (this->m_hugint.at(i) != arg.m_hugint.at(i))
			{
				return false;
			}
		}

	}
	return true;
}

inline Hugeint Hugeint::operator+(const Hugeint& arg) const
{
	int len = std::max(this->m_hugint.size(), arg.m_hugint.size()) + 1;
    std::string result(len,0);
	std::string s1 = this->m_hugint;
	std::string s2 = arg.m_hugint;
	std::reverse(s1.begin(), s1.end());
    std::reverse(s2.begin(), s2.end());
	for (int i = 0; i < result.size(); ++i)
	{
		if (i < s1.size())
		{
			result.at(i) += (s1.at(i) - 48);
		}
		if (i < s2.size())
		{
			result.at(i) += (s2.at(i) - 48);
		}
	}
	for (int i = 0; i < result.size(); ++i)
	{
		if (result.at(i) > 9)
		{
			result.at(i + 1) += result.at(i) / 10;
			result.at(i) %= 10;	
		}
        result.at(i) += 48;
	}
	std::reverse(result.begin(), result.end());
	this->correction(result);
	Hugeint h(result);
	return h;
}

inline Hugeint Hugeint::operator-(const Hugeint& arg) const
{
	if (arg <= (*this))
	{
		std::string result = this->m_hugint;
		std::string s1 = arg.m_hugint;
		std::reverse(s1.begin(), s1.end());
		std::reverse(result.begin(), result.end());

		for (int i = 0; i < result.size(); ++i)
		{
			if (i < s1.size())
			{
				if (result.at(i) < s1.at(i))
				{
					result.at(i) += 10;
					--result.at(i + 1);
				}
				result.at(i) += 48;
				result.at(i) -= s1.at(i);
			}
		}
		/*for (int i = 0; i < result.size(); ++i)
		{
			result.at(i) += 48;
		}*/
		std::reverse(result.begin(), result.end());
		this->correction(result);
        Hugeint h(result);
	    return h;
	}
	return Hugeint(0);
}

inline Hugeint Hugeint::operator*(const Hugeint& arg) const
{
	int len = this->m_hugint.size() + arg.m_hugint.size();
	std::string result(len, 0);
	std::string s1 = this->m_hugint;
	std::string s2 = arg.m_hugint;
	std::reverse(s1.begin(), s1.end());
	std::reverse(s2.begin(), s2.end());
	int index = 0;
	for (int i = 0; i < s1.size(); ++i)
	{
		s1.at(i) -= 48;
	}
	for (int i = 0; i < s2.size(); ++i)
	{
		s2.at(i) -= 48;
	}
	for (int i = 0; i < s1.size(); ++i)
	{
		index = i;
		for (int j = 0; j < s2.size(); ++j)
		{
			result.at(index + j) += (s1.at(i) * s2.at(j));
			if (result.at(index + j) > 9)
			{
				result.at(index + j + 1) += result.at(index + j) / 10;
				result.at(index + j) %= 10;
			}
		}
	}
	for (int i = 0; i < result.size(); ++i)
	{
		if (result.at(i) > 9)
		{
			result.at(i + 1) += result.at(i) / 10;
			result.at(i) %= 10;
		}
		result.at(i) += 48;
	}
	std::reverse(result.begin(), result.end());
	this->correction(result);
	Hugeint h(result);
	return h;
}

inline Hugeint Hugeint::operator/(const Hugeint& arg) const
{
	if (arg <= (*this))
	{
		Hugeint s1 = arg;
		Hugeint s2 = this->m_hugint;
		std::string result;
		Hugeint curent(0);
		int iter = 0;
		if (s1 <= s2)
		{
			while (s2.m_hugint.size() > 0)
			{
				if (iter == 0)
				{
					curent.m_hugint.clear();
					curent.m_hugint.insert(curent.m_hugint.end(), s2.m_hugint.begin(), s2.m_hugint.begin() + s1.m_hugint.size());
					s2.m_hugint.erase(s2.m_hugint.begin(), s2.m_hugint.begin() + s1.m_hugint.size());

					if (curent <= s1 && !(curent == s1))
					{
						curent.m_hugint.push_back(s2.m_hugint.at(0));
						s2.m_hugint.erase(s2.m_hugint.begin(), s2.m_hugint.begin() + 1);
					}
				}
				else
				{
					if (s2.m_hugint.size() > 0)
					{
						curent.m_hugint.push_back(s2.m_hugint.at(0));
						s2.m_hugint.erase(s2.m_hugint.begin(), s2.m_hugint.begin() + 1);
						if (s2.m_hugint.size() == 0 && curent < s1)
						{
							for (int i = 0; i < curent.m_hugint.size(); ++i)
							{
								result.push_back('0');
							}
							curent.m_hugint.clear();
							break;
						}
					}
					while (curent < s1 && s2.m_hugint.size() > 0)
					{
						curent.m_hugint.push_back(s2.m_hugint.at(0));
						s2.m_hugint.erase(s2.m_hugint.begin(), s2.m_hugint.begin() + 1);
						result.push_back('0');
					}

				}

				int k = 0;
				for (int i = 2; i <= 10; ++i)
				{
					if (curent < (s1 * Hugeint(std::to_string(i))))
					{
						k = i - 1;
						result.push_back(std::to_string(k).at(0));
						break;
					}
				}

				curent = curent - (s1 * Hugeint(std::to_string(k)));
				//s2.m_hugint.insert(s2.m_hugint.begin(), curent.m_hugint.begin(), curent.m_hugint.end());
				if (curent.m_hugint.empty())
				{
					while (s2.m_hugint.size() > 0 && s2.m_hugint.at(0) == '0')
					{
						result.push_back('0');
						s2.m_hugint.erase(s2.m_hugint.begin(), s2.m_hugint.begin() + 1);

					}
					curent.m_hugint.clear();
				}

				++iter;
			}
		}

		Hugeint h(result);
		return h;
	}
	return Hugeint(0);
}

inline Hugeint& Hugeint::operator=(const Hugeint& arg) 
{
	if (this != &arg)
	{
		this->m_hugint.resize(arg.m_hugint.size());
		for (int i = 0; i < arg.m_hugint.size(); ++i)
		{
			this->m_hugint.at(i) = arg.m_hugint.at(i);
		}
	}
	return *this;
}

inline std::ostream& operator<<(std::ostream& out, const Hugeint& ob)
{
	out << ob.m_hugint;	
	return out;
}