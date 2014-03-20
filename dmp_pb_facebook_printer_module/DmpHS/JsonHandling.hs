{-# LANGUAGE OverloadedStrings #-}

module DmpHS.JsonHandling
( Album
, AlbumList
, AlbumCreationResponse
, Privacy
, FacebookException
, getAlbumID
) where

import System.IO
import Data.Aeson ((.:), (.=), (.:?))
import Data.Maybe (fromJust)
import qualified Data.Aeson as Aeson
import Control.Applicative
import qualified Data.ByteString.Lazy.Char8 as ByteString
import Control.Monad
import qualified Data.HashMap.Strict as HashMap

-- Facebook Album JSON and supporting types/instances

data Album = Album { albumName        :: String
                   , albumID          :: String
                   } deriving (Show)

instance Aeson.FromJSON Album where
   parseJSON (Aeson.Object v) = Album       <$>
                                v .: "name" <*>
                                v .: "id"

-- Facebook Album List JSON and supporting types/instances
      
newtype AlbumList = AlbumList { albumList :: [Album]
                              } deriving (Show)
                              
instance Aeson.FromJSON AlbumList where
   parseJSON (Aeson.Object v) = AlbumList <$> v .: "data"
   
-- Facebook Album Creation response JSON and supporting types/instances

newtype AlbumCreationResponse = AlbumCreationResponse {responseID :: String
                                                      } deriving (Show)
                                                      
instance Aeson.FromJSON AlbumCreationResponse where
   parseJSON (Aeson.Object v) = AlbumCreationResponse <$> v .: "id"

-- Facebook Privacy Object JSON and supporting types/instances

data Privacy = Everyone | AllFriends | FriendsOfFriends | Self

instance Show Privacy where
   show Everyone         = "EVERYONE"
   show AllFriends       = "ALL_FRIENDS"
   show FriendsOfFriends = "FRIENDS_OF_FRIENDS"
   show Self             = "SELF"
                                  
instance Aeson.ToJSON Privacy where
   toJSON p = Aeson.object ["value" .= (show p)]

-- Facebook Exception Response JSON and supporting types/instances

data FacebookException = FacebookException { facebookExceptionMessage :: String
                                           , facebookExceptionType    :: String
                                           , facebookExceptionCode    :: Int
                                           , facebookExceptionSubCode :: Maybe Int
                                           } 

instance Aeson.FromJSON FacebookException where
   parseJSON (Aeson.Object v) = FacebookException                 <$>
                                (error >>= (.: "message"))        <*>
                                (error >>= (.: "type"))           <*>
                                (error >>= (.: "code"))           <*>
                                (error >>= (.:? "error_subcode"))
                                where error = (v .: "error")
                                
instance Show FacebookException where
   show (FacebookException m t c Nothing) = t ++ " " ++ (show c) ++ ": " ++ m
   show (FacebookException m t c (Just s))  = t ++ " " ++ (show c) ++ ", " ++ (show s) ++ ": " ++ m

-- Helper functions
   
getAlbumID :: String -> AlbumList -> Maybe String
getAlbumID [] _                 = Nothing
getAlbumID _ (AlbumList [])     = Nothing
getAlbumID s (AlbumList (x:xs))
   | albumName x == s = Just $ albumID x
   | otherwise        = getAlbumID s $ AlbumList xs
