
#include <string>
#include <sstream>
#include <vector>

void SplitString(std::vector<std::string> & theStringVector,  /* Altered/returned value */
	const  std::string  & theString,
	const  std::string  & theDelimiter)
{
	size_t  start = 0, end = 0;

	while (end != std::string::npos)
	{
		end = theString.find(theDelimiter, start);

		// If at end, use length=maxLength.  Else use length=end-start.
		theStringVector.push_back(theString.substr(start,
			(end == std::string::npos) ? std::string::npos : end - start));

		// If at end, use start=maxSize.  Else use start=end+delimiter.
		start = ((end > (std::string::npos - theDelimiter.size()))
			? std::string::npos : end + theDelimiter.size());
	}
}


template <typename T>
T StringToNumber(const std::string &Text)
{
	std::stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}