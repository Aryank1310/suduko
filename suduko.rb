class Sudoku
  def initialize(board_string)
    @board = board_string.chars.map(&:to_i).each_slice(9).to_a
  end

  def solve
    solve_board
    to_s
  end

  def to_s
    @board.map { |row| row.join(' ') }.join("\n")
  end

  private

  def solve_board(row = 0, col = 0)
    return true if row == 9

    next_row, next_col = next_position(row, col)

    if @board[row][col] != 0
      solve_board(next_row, next_col)
    else
      (1..9).each do |num|
        if valid_move?(row, col, num)
          @board[row][col] = num
          return true if solve_board(next_row, next_col)
        end
      end
      @board[row][col] = 0
      false
    end
  end

  def next_position(row, col)
    if col == 8
      [row + 1, 0]
    else
      [row, col + 1]
    end
  end

  def valid_move?(row, col, num)
    return false if @board[row].include?(num)
    return false if @board.transpose[col].include?(num)
    return false if subgrid(row, col).include?(num)

    true
  end

  def subgrid(row, col)
    subgrid_row = (row / 3) * 3
    subgrid_col = (col / 3) * 3
    @board[subgrid_row, 3].map { |r| r[subgrid_col, 3] }.flatten
  end
end

board_string = '530070000600195000098000060800060003400803001700020006060000280000419005000080079'
sudoku = Sudoku.new(board_string)
puts sudoku.solve
