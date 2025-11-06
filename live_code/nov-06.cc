#include <vector>


class ITable {
    public:
    enum class Action {
        Stand,
        Hit,
        Double,
        Split
    };

    enum class Result {
        Ok,
        Illegal
    };
    enum class Value {
        ACE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        end
    };

    enum class Suit {
        HEARTS,
        CLUBS,
        SPADES,
        DIAMONDS,
        end
    };

    struct Card {
        Value value_;
        Suit suit_;
    };

    std::vector<Card> GetHand(int player_index,int hand_index) const;
    int GetNumberOfHands(int player_index) const;

    int GetPlayerCurrentBet(int player_index,int hand_index) const;
    int GetPlayerMoney(int player_index) const;

    Card GetDealerCard() const;

    // Dealer es parte de la mesa, no tiene elecciones propias mas alla de aplicar las reglas
    void DealCard(int player_index,int hand_index);

    PlaySafeBet(int player_index);
    Result ApplyPlayerAction(int player_index,int hand_index,Action action);


    CleanTable
    CalculateWinnings
    PlayerAction


        // CheckPlayersLeft
        // CleanHands
        // CleanBets
        // PlaceInitialBet
        // Shuffle
        // Deal 2 cards per player
        // Deal 1 card to dealer

    // InsuranceOffer
        // Player is asked if they want insurance, in case of an ace

    // Fpr each player they can do actions until they overflow or stand
    // PlayerTurn
        // Player is given the board to check and
        // reply with an action
        // Stand
        // Hit
        // Double
        // Split

    // When all players have stood, dealer draws out cards up to their max



    ShuffleCards
    PlaceBet
    MinBet
    MaxBet

    DealerStop

    PlayerCount

    
    

};

class IPlayer {

};

class IGame {

};