# all: gene_count run
# gene_count: gene_count.cpp
# 	g++ -Wall -g gene_count.cpp -o gene_count
# run:
# 	./gene_count
# all: most_freq_kmer run
# most_freq_kmer: most_freq_kmer.cpp
# 	g++ -Wall -g most_freq_kmer.cpp -o most_freq_kmer
# run:
# 	./most_freq_kmer
# all: reverse_complement_problem run
# reverse_complement_problem: reverse_complement_problem.cpp
# 	g++ -Wall -g reverse_complement_problem.cpp -o reverse_complement_problem
# run:
# 	./reverse_complement_problem
# all: pattern_matching_problem run
# pattern_matching_problem: pattern_matching_problem.cpp
# 	g++ -Wall -g pattern_matching_problem.cpp -o pattern_matching_problem
# run:
# 	./pattern_matching_problem
# all: clump_finding_problem run
# clump_finding_problem: clump_finding_problem.cpp
# 	g++ -Wall -g clump_finding_problem.cpp -o clump_finding_problem
# run:
# 	./clump_finding_problem
# all: minimum_skew_problem run
# minimum_skew_problem: minimum_skew_problem.cpp
# 	g++ -Wall -g minimum_skew_problem.cpp -o minimum_skew_problem
# run:
# 	./minimum_skew_problem
# all: approximate_pattern_matching_problem run
# approximate_pattern_matching_problem: approximate_pattern_matching_problem.cpp
# 	g++ -Wall -g approximate_pattern_matching_problem.cpp -o approximate_pattern_matching_problem
# run:
# 	./approximate_pattern_matching_problem
# all: freq_words_with_mism run
# freq_words_with_mism: freq_words_with_mism.cpp
# 	g++ -Wall -g freq_words_with_mism.cpp -o freq_words_with_mism
# run:
# 	./freq_words_with_mism
all: main run
main: new_main.cpp reverse_complement_problem.o pattern_matching_problem.o clump_finding_problem.o minimum_skew_problem.o approximate_pattern_matching_problem.o freq_words_with_mism.o antibiotics.o motif_finding.o
	g++ -Wall -O0 -g new_main.cpp reverse_complement_problem.o pattern_matching_problem.o clump_finding_problem.o minimum_skew_problem.o approximate_pattern_matching_problem.o freq_words_with_mism.o antibiotics.o motif_finding.o -o main1
reverse_complement_problem.o: reverse_complement_problem.cpp
	g++ -Wall -O3 -g -c reverse_complement_problem.cpp -o reverse_complement_problem.o
pattern_matching_problem.o: pattern_matching_problem.cpp
	g++ -Wall -O3 -g -c pattern_matching_problem.cpp -o pattern_matching_problem.o
clump_finding_problem.o: clump_finding_problem.cpp
	g++ -Wall -O3 -g -c clump_finding_problem.cpp -o clump_finding_problem.o
minimum_skew_problem.o: minimum_skew_problem.cpp
	g++ -Wall -O3 -g -c minimum_skew_problem.cpp -o minimum_skew_problem.o
approximate_pattern_matching_problem.o: approximate_pattern_matching_problem.cpp
	g++ -Wall -O3 -g -c approximate_pattern_matching_problem.cpp -o approximate_pattern_matching_problem.o
freq_words_with_mism.o: freq_words_with_mism.cpp
	g++ -Wall -O3 -g -c freq_words_with_mism.cpp -o freq_words_with_mism.o
antibiotics.o: antibiotics.cpp
	g++ -Wall -O0 -g -c antibiotics.cpp -o antibiotics.o
motif_finding.o: motif_finding.cpp
	g++ -Wall -O0 -g -c motif_finding.cpp -o motif_finding.o
run:
	./main1
