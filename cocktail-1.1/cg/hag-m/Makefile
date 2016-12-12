SPEC	= hag
MC	= mc -d ../../reuse/src

Main:
	cg -dimDI0 $(SPEC);
	echo p Main | $(MC)

test:
	cg -dimwDI $(SPEC);
	echo p Main | $(MC)
	echo 5 4 3 2 1 0 | Main
	cg -IT $(SPEC);
	echo p Main | $(MC)
	echo 2 0 | Main
	cg -IX $(SPEC);
	echo p Main | $(MC)
	echo 2 0 | Main
	cg -IY $(SPEC);
	echo p Main | $(MC)
	echo 2 0 | Main
	cg -IZ $(SPEC);
	echo p Main | $(MC)
	echo F > TraceTab
	echo 2 0 | Main
	cg -ITU $(SPEC);
	echo p Main | $(MC)
	echo 2 0 | Main
	cg -IXU $(SPEC);
	echo p Main | $(MC)
	echo 2 0 | Main
	cg -IYU $(SPEC);
	echo p Main | $(MC)
	echo 2 0 | Main
	cg -IZU $(SPEC);
	echo p Main | $(MC)
	echo 2 0 | Main

clean:
	rm -f TraceTab Main Tree.* Eval.* Main.[dimor]
