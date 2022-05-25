# plan

## plan

- [x] 課題の要約の作成
- [x] todoの作成
- [x] dockerでclang++でmakeできるようにする
  - [x] 簡単なmakefileの作成
  - [x] docker内でmakeできるようにする
- [x] コンテナの作成に関する参照サイトのまとめ
- [ ] テストの作成とイメージづけのためのヘッダーファイルの作成
  - [ ] テストのテンプレの作成
    - [x] 出力のひな形
    - [x] 値の出力
    - [x] 時間計測
      - [x] 選定->clock
      - [x] 作成
  - [ ] 実装するものの本物の挙動の確認
    - [x] std::allocator
    - [x] iterators_traits
    - [x] reverse_iterator
    - [x] enable_if
    - [x] is_integral
    - [x] equal/lexicographical compare
    - [x] std::pair
    - [x] std::make_pair
    - [ ] vector
      - [ ] コンストラクタで大量に確保
    - [ ] map
    - [ ] stack
- 中身の作成
  - [x] iterators_traits
  - [x] reverse_iterator
  - [x] enable_if
  - [x] is_integral
  - [x] equal/lexicographical compare
  - [x] std::pair
  - [x] std::make_pair
  - [ ] vector
    - [ ] iteratorの種類に応じた方法
    - [ ] input_iteratorかどうかの確認
  - [ ] map
  - [ ] stack

## issue

- [ ] make docker時にlogを標準出力する
- [ ] test通す
  - https://github.com/mli42/containers_test.git
  - https://github.com/mfunyu/tester_ft_containers.git
