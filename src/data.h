// Copyright 2004-, Facebook, Inc. All Rights Reserved.

/* This is the basic class of internal data handler.
 * It loads data from file and stores it in internal format for easy access
 * at training/testing time.
 *
 * It also provides random RHS sampling for negative sampling in training.
 */

#pragma once

#include "dict.h"
#include "parser.h"
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

namespace starspace {
extern long dbg_cotap_hit_acc;
extern long dbg_cotap_try_acc;
class InternDataHandler {
public:
  explicit InternDataHandler(std::shared_ptr<Args> args);

  virtual void loadFromFile(const std::string& file,
                            std::shared_ptr<DataParser> parser);
  virtual void convert(const ParseResults& example, ParseResults& rslt) const;

  virtual void getRandomRHS(const ParseResults& s, std::vector<Base>& results)
    const;
  virtual void getRandomNegRHS(const ParseResults& ex, std::vector<Base>& result) const; 
  virtual void save(std::ostream& out);

  virtual void getWordExamples(int idx, std::vector<ParseResults>& rslt) const;
  void readCotap(const std::string &file) ;
  void getWordExamples(
      const std::vector<Base>& doc,
      std::vector<ParseResults>& rslt) const;

  void addExample(const ParseResults& example);

  void getExampleById(int32_t idx, ParseResults& rslt) const;

  void getNextExample(ParseResults& rslt);

  void getRandomExample(ParseResults& rslt) const;

  void getKRandomExamples(int K, std::vector<ParseResults>& c);

  void getNextKExamples(int K, std::vector<ParseResults>& c);

  size_t getSize() const { return size_; };

  void errorOnZeroExample(const std::string& fileName);

  void initWordNegatives();
  void getRandomWord(std::vector<Base>& result);
  bool isCotap(const DocInfo &pos, const DocInfo& neg, const int tid=0) const;

protected:
  virtual Base genRandomWord() const;

  static const int32_t MAX_VOCAB_SIZE = 10000000;
  static const int32_t MAX_WORD_NEGATIVES_SIZE = 10000000;

  std::shared_ptr<Args> args_;
  std::vector<ParseResults> examples_;

  int32_t idx_ = -1;
  int32_t size_ = 0;

  int32_t word_iter_;
  std::vector<Base> word_negatives_;
  std::unordered_set<std::string> cotaps_;
};

}
