Stefan Theard PSID: 1208198

Keyword Search (HW06)

I decided to not include the count at all in the output of this program, adding this note because the PDF says to do so.

This program uses a hash table and a hashing algorithm to parse given files from a corpus
and store them into a hash table for O(1) time complexity in most cases. Collisions are dealt with by using chaining. The hashing algorithm used in this program is proprietary to Stefan Theard and it is as follows:

hash(string word)
double sum = 0;
	for(unsigned int i = 0; i < word.length() ; i++)
	{
		sum = sum + static_cast<int>(word.at(i));
		sum = sum + sum/7;
		sum+=3;
	}
	sum = sum + 15;
	sum = sum*(sum/2);
	return (static_cast<int>(sum)%table_size);

After a lot of testing this algorithm had the best results with ~2500 words there were only 50 collisions, down from 600 with a basic hashing algorithm.

An AVL height balanced tree is also used for stop-word removal using the filter() command in the script file.