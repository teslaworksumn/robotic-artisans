gcodeHeader = """G21 (set to mm units)
M3 S225 (initalize servo control)
"""

def prepend():
    return gcodeHeader