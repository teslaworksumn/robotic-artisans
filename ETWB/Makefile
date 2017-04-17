art: image_processor.py main.py planner.py planner.pyc GCoder.py Interpolate.py main2.m InverseKinematicsSolverLITE.m GCodeSpitter2.m
	python3 image_processor.py picture.jpg picture.ptg
	python main.py picture.ptg strokes.txt
	python GCoder.py
	python Interpolate.py xyz.txt xyzi.txt

clean:
	rm -f *.txt *.ptg
