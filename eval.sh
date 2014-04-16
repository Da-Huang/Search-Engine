EVAL=../trec_eval.8.1/trec_eval
mkdir -p ../eval
$EVAL -q ../data/04.qrels.12-Nov-04 ../res/04.txt \
		| tee ../eval/04.eval
$EVAL -q ../data/05.adhoc_qrels ../res/05.txt \
		| tee ../eval/05.eval
$EVAL -q ../data/05.np_qrels ../res/05.np.txt \
		| tee ../eval/05.np.eval
$EVAL -q ../data/qrels.all ../res/06.701.txt \
		| tee ../eval/06.701.eval
$EVAL -q ../data/qrels.tb06.top50 ../res/06.801.txt \
		| tee ../eval/06.801.eval
$EVAL -q ../data/qrels.tb06.infAP ../res/06.801.txt \
		| tee ../eval/06.801.inf.eval
$EVAL -q ../data/qrels.tb06.np ../res/06.np.txt \
		| tee ../eval/06.np.eval
