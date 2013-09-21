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
all: approximate_pattern_matching_problem run
approximate_pattern_matching_problem: approximate_pattern_matching_problem.cpp
	g++ -Wall -g approximate_pattern_matching_problem.cpp -o approximate_pattern_matching_problem
run:
	./approximate_pattern_matching_problem
