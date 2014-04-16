mkdir -p ../res
 ./main -search-trec ../tw-index ../data/04topics.701-750 \
	 | tee ../res/04.txt
 ./main -search-trec ../tw-index ../data/05.topics.751-800 \
	 | tee ../res/05.txt
 ./main -search-trec ../tw-index ../data/05.np_topics.601-872.final \
	 | tee ../res/05.np.txt
 ./main -search-trec ../tw-index ../data/06.topics.701-850 \
	 | tee ../res/06.701.txt
 ./main -search-trec ../tw-index ../data/06.topics.801-850 \
	 | tee ../res/06.801.txt
 ./main -search-trec ../tw-index ../data/06.np_topics.901-1081 \
	 | tee ../res/06.np.txt

