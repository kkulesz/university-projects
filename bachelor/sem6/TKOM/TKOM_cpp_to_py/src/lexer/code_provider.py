class CodeProvider:
    def __init__(self, input_stream):
        self.line = 1
        self.column = 1
        self.stream = input_stream
        self.curr_char = self.stream.read(1)

    def get_char(self):
        return self.curr_char

    def move_to_next_char(self):
        self.curr_char = self.stream.read(1)

        if self.curr_char == '\n':
            self.line += 1
            self.column = 1
        else:
            self.column += 1

    def move_and_get_char(self):
        self.move_to_next_char()
        return self.get_char()

    def get_position(self):
        return self.line, self.column
