/**
    turingMachine.cpp
    Purpose: Create and execute Turing Machines in a brute force manner.

    @author Jorge Miguel Ferreira da Silva
    @version 0.1
*/

#include "turingMachine.h"

bool TuringRecord::next(size_t number_of_states, size_t alphabet_size) {
  if (write < alphabet_size - 1) {
    write += 1;
    return true;
  }
  write = 0;
  if (move < 2) {
    move += 1;
    return true;
  }

  move = 0;
  if (state < number_of_states - 1) {
    state += 1;
    return true;
  }

  state = 0;
  return false;
}

std::ostream& operator<<( std::ostream& o, const TuringRecord& r) {
  o << "(" << r.write << "," << r.move << "," << r.state << ")";
  return o;
}

TuringRecord TuringRecord::by_index(unsigned long long id, size_t number_of_states, size_t alphabet_size) {
  // order of significance (least to most): character_write -> tape_move -> state
  unsigned long long nstates = number_of_states;
  unsigned long long nalphabet = alphabet_size;
  auto rest = id;
  auto write = static_cast<Char>(rest % nalphabet);
  rest /= nalphabet;
  auto move = static_cast<Move>(rest % 3);
  rest /= 3;
  auto state = static_cast<State>(rest % nstates);
  return TuringRecord { write, move, state };
}

StateMatrix::StateMatrix(size_t number_of_states, size_t alphabet_size):
  v(alphabet_size * number_of_states, TuringRecord{0, 0, 0}), nbStates(number_of_states), alphSz(alphabet_size){}

void StateMatrix::set_by_index(unsigned long long id) {
  auto rest = id;
  auto record_cardinality = this->nbStates * this->alphSz * 3;
      INPUT = Fopen(argv[argc-1], "r"); 
  nSeq = 0;
  maxName = 0;
  filtered = 0;
  while((sym = fgetc(INPUT)) != EOF){

    if(sym == '$' || sym == '#'){
      if(fscanf(INPUT, "\t%lf\t%"PRIu64"\t%s\n", &fvalue, &fsize, fname) != 3){
        fprintf(stderr, "  [x] Error: unknown type of file!\n");
        exit(1);
        }

      if(PEYE->best == 1){
        if(regexec(&regexCompiled, fname, 2, groupArray, 0) == 0){
          char sourceCopy[strlen(fname) + 1];
          strcpy(sourceCopy, fname);
          sourceCopy[groupArray[1].rm_eo] = 0;
          if(SearchSLabels(SL, sourceCopy + groupArray[1].rm_so) == 0){
            ++unique;
            AddSLabel(SL, sourceCopy + groupArray[1].rm_so);
            UpdateSLabels(SL);
            }
          else{
            ++filtered;
            continue;
            }
          }
        }

      if(fsize > PEYE->upperSize ||  fsize < PEYE->lowerSize ||
        fvalue > PEYE->upperSimi || fvalue < PEYE->lowerSimi){
        ++filtered;
        continue;
        }

      if(fsize > maxSize)
        maxSize = fsize;
 
      if(PEYE->best == 1){
        if((tmp = strlen(SL->names[SL->idx-1])) > maxName)
          maxName = tmp;
        }
      else{
        if((tmp = strlen(fname)) > maxName)
          maxName = tmp;
        }
      ++nSeq;
      }
    }
  rewind(INPUT);
    
  for (auto& st: this->v) {
    auto state_id = rest % record_cardinality;
    st = TuringRecord::by_index(state_id, this->nbStates, this->alphSz);
    rest /= record_cardinality;
    if (rest == 0) break;
  }
}

TuringRecord& StateMatrix::at(Char alph, State state){
  return this->v.at(   (   (alph + 1) * this->nbStates   )   -   (   this->nbStates - state  )   );
}

const TuringRecord& StateMatrix::at(Char alph, State state) const {
  return this->v.at(   (   (alph + 1) * this->nbStates   )   -   (   this->nbStates - state  )   );
}

bool StateMatrix::next(){
  for(auto& e: v) {
    if (e.next(nbStates, alphSz)) {
      return true;
    }
  }
  return false;
}

void StateMatrix::print() const{
    std::cout << std::endl << "Turing Machine State Matrix" << std::endl<<"     ";

    std::cout << std::endl;
 
    std::cout << "   ";

    for (auto jj=0u;jj< nbStates ; jj++){
      std::cout<<"    "<< jj << "     ";
    }
  
    std::cout << std::endl<< "   ";
     for (auto jj=0u;jj< nbStates ; jj++){
      std::cout<<"----------";
    }
    std::cout << std::endl;
    
    
FILTER *FIL = CreateFilter(PEYE->windowSize, PEYE->sampling, PEYE->windowType, 
  PEYE->threshold);
  INPUT = Fopen(argv[argc-1], "r"); 
  while((sym = fgetc(INPUT)) != EOF){
    if(sym == '#'){
      if(fscanf(INPUT, "\t%lf\t%"PRIu64"\t%s\n", &fvalue, &fsize, fname) != 3){
        fprintf(stderr, "  [x] Error: unknown type of file!\n");
        exit(1);
        }

      if(fsize > PEYE->upperSize ||  fsize < PEYE->lowerSize ||
        fvalue > PEYE->upperSimi || fvalue < PEYE->lowerSimi)
        continue;

      fprintf(stderr, "  [+] Filtering & segmenting %s ... ", fname);
      fprintf(OUTPUT, "$\t%lf\t%"PRIu64"\t%s\n", fvalue, fsize, fname);
      InitEntries(FIL, fsize, INPUT);
      FilterStream(FIL, OUTPUT);
      DeleteEntries(FIL);
      fprintf(stderr, "Done!\n");
      }
    }
  DeleteFilter(FIL);
    
    for (auto ii=0u;ii< alphSz ; ii++){
        auto line = chr_line(ii);
        std::cout <<" " << ii << " |";
        for (auto jj=0u;jj< nbStates ; jj++){
          auto& r = line[jj];
          std::cout << r << " | ";
        }
        std::cout << std::endl;
    }
      
    std::cout << std::endl << "Lines --> Alphabet Letter "<< std::endl << "Columns --> TM State "<< std::endl;
    std::cout << "(w,m,s) --> (write,move,state)" << std::endl;

  }

const TuringRecord* StateMatrix::chr_line(Char c) const {
  return this->v.data() + c * this->nbStates;
}

Tape::Tape():
  tape(256, 0), position(128), max_size(256),ind_left(position-1),ind_right(position+1){}

Char Tape::getvalue() {
  return this->tape[this->position];
}

size_t Tape::getposition() {
return this->position;
}

/**
    Given a relative position and a value this function:
    - changes the position on the tape;
    - writes new value on the tape on the new position.
    
    It also:
    - Alocates space to the left or the right of the tape if the max_size is exceeded;
    - defines if index positions of the left and right of the tape have changed.

    @param relativePos . Relative position that the tm must move in the tape.
    @param value. Value that the Tm must write on the Tape.
    @return TapeMoves. Structure TapeMoves(previousValue,moveRight,moveLeft)
*/
TapeMoves Tape::moveandSet(Move relativePos, Char value) {

  TapeMoves tapeMove{0,false,false};
  int replace_pos = relativePos - 1;
  this->position += replace_pos;
  
  if (this->position >= this->ind_right){
      this->ind_right = this->position+1;
      tapeMove.moveRight = true;
  }
      
  else if (this->position <= this->ind_left){
      this->ind_left = this->position-1;
      tapeMove.moveLeft=true;
  }

  if (this->position >= this->max_size) {
    this->reserve_right(this->max_size);
  } 
  else if (this->position == 0) {
    this->reserve_left(this->max_size);
  }
  tapeMove.previousValue = this->tape[this->position];
  this->tape[this->position] = value;
  return tapeMove;
}

void Tape::resetTape() {
  std::fill(this->tape.begin(), this->tape.end(), 0);
  this->position = this->tape.size() / 2;
  this->ind_left = this->position-1;
  this->ind_right = this->position+1;
}

void Tape::reserve_right(size_t amount) {
    this->max_size += amount;
    this->tape.resize(this->max_size);
}

void Tape::reserve_left(size_t amount) {
  this->max_size += amount;
  std::vector<Char> tape2 = this->tape;
  std::fill(this->tape.begin(), this->tape.end(), 0);
  this->tape.resize(amount);
  this->tape.insert(tape.end(), tape2.begin(), tape2.end());
  this->position = this->position + amount;
  this->ind_right = this->ind_right + amount;
  this->ind_left = this->ind_left + amount;
}

/* prints written part of the tape.*/
void Tape::print(){
  for (auto i = this->tape.begin() + this->ind_left; i != this->tape.begin() + this->ind_right; ++i)
    std::cout << *i << ' ';
    
  std::cout<< std::endl;
} 


std::ostream& operator<<( std::ostream& o, const Tape& t) {
  auto start = std::find_if(t.tape.begin(), t.tape.end(), [](auto c) { return c != 0; });
  auto end = std::find_if(t.tape.rbegin(), t.tape.rend(), [](auto c) { return c != 0; }).base() + 1;
  if (end <= start) {
    end = start + 1;
  }
  for (auto it = start; it != end; ++it) {
    std::cout << *it;
  }
  return o;
}


TuringMachine::TuringMachine(size_t number_of_states, size_t alphabet_size):
  state(0), turingTape(), stMatrix(number_of_states,alphabet_size){}

TapeMoves TuringMachine::act(){
    TapeMoves tpMove;
    Char alphValue = turingTape.getvalue();
    auto tr = stMatrix.at(alphValue, this->state);
    tpMove = turingTape.moveandSet(tr.move, tr.write);
    this->state = tr.state;
    return tpMove;
}

void TuringMachine::reset_tape_and_state(){
 this->turingTape.resetTape();
 this->state=0;
}


