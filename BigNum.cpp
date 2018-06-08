class BigNum {
public:
	BigNum(int x) : data_(std::to_string(x)) {}
	BigNum(string x) : data_(x) {
		Trim();
	}

	std::string String() { return data_.empty() ? "0" : data_; }

	BigNum Add(BigNum other) {
		std::string& A = data_;
		std::string& B = other.data_;

		bool carry = false;
		std::string res = "";
		int idx1 = A.size() - 1;
		int idx2 = B.size() - 1;
		while (idx1 >= 0 && idx2 >= 0) {
			res += GetDigitSum(A[idx1--], B[idx2--], &carry);
		}
		
		while (idx1 >= 0) {
			res += GetDigitSum(A[idx1--], &carry);
		}
		
		while (idx2 >= 0) {
			res += GetDigitSum(B[idx2--], &carry);
		}

		if (carry) {
			res += '1';
		}

		std::reverse(res.begin(), res.end());

		return BigNum(res);
	}

	BigNum Multiply(BigNum other) {
		std::string& A = data_;
		std::string& B = other.data_;

		BigNum res(0);
		int level = 0;
		for (int i = A.size() - 1; i >= 0; i--) {
			std::string tmp;
			tmp.resize(level++);
			fill(tmp.begin(), tmp.end(), '0');

			int carry = 0;
			for (int j = B.size() - 1; j >= 0; j--) {
				tmp += GetDigitMulti(A[i], B[j], &carry);
			}
			if (carry) {
				tmp += (carry + '0');
			}
			std::reverse(tmp.begin(), tmp.end());

			res = res.Add(tmp);
		}
		return res;
	}
private:
	void Trim() {
		std::reverse(data_.begin(), data_.end());
		int idx = data_.size() - 1;
		while (idx >= 0 && data_[idx] == '0') {
			idx--;
		}
		data_.resize(idx + 1);
		std::reverse(data_.begin(), data_.end());
	}

	char GetDigitMulti(char digit1, char digit2, int* carry) {
		char res = ((digit1 - '0') * (digit2 - '0')) + *carry;
		*carry = 0;
		if (res >= 10) {
			*carry = res/10;
			res = res % 10;
		}
		return res + '0';
	}
	char GetDigitSum(char digit, bool* carry) {
		char res = (digit - '0') + *carry;
		if (res >= 10) {
			res -= 10;
			*carry = true;
		} else {
			*carry = false;
		}
		return res + '0';
	}

	char GetDigitSum(char digit1, char digit2, bool* carry) {
		char res = (digit1 - '0') + (digit2 - '0') + *carry;
		if (res >= 10) {
			res -= 10;
			*carry = true;
		} else {
			*carry = false;
		}
		return res + '0';
	}

	std::string data_;
};