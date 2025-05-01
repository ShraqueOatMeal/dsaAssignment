class oneStarReview {
    public:
        static void analyzeTopWords(LinkList<reviews>& reviewList);
        static void analyzeTopWords(reviews* reviewArray, int reviewCount); // <-- NEW
    };
    